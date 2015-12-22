#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "ts_net_server.h"

void NetServer::recv(NetServer::socket_ptr sock) 
{
    int keep = 1;
    while (keep) 
    {
        streambuf buf;
        NetCmd nc;
        boost::system::error_code ec;

        if (!read_until(*sock, buf, "\r\n", ec)) 
        {
            std::cout << "client disconnect: " << ec << std::endl; 
            break;
        }

        std::istream in(&buf);

        in.read((char*)&(nc.h), sizeof(nc.h));

        switch ((nc.h.type))
        {
            case 1:
                in.get(nc.cmd, nc.h.length);
                nc.cmd[nc.h.length] = '\0';
                std::cout << "CMD: " << nc.cmd << std::endl;
                write(*sock, buffer("OK", 2));
                break;
            default: 
                keep = 0;
                break;
        }
    }
}


NetServer::NetServer(int portnum) :
    m_portno(portnum),
    m_active(1), 
    m_ep(ip::tcp::v4(), portnum),
    m_acc(m_service, m_ep)
{
}


NetServer::~NetServer() 
{
}

void NetServer::start() 
{
    while(m_active) 
    {
        socket_ptr sock(new ip::tcp::socket(m_service));
        ip::tcp::endpoint cli;

        m_acc.accept(*sock, cli);
        
        boost::thread t = boost::thread(boost::bind(&NetServer::recv, this, sock));
        t.join();
    }
}

