#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <boost/asio.hpp>

using namespace boost::asio;

struct NetCmdHeader
{
    uint16_t type;
    uint16_t length;
    uint32_t hash;
};

struct NetCmd
{
    NetCmdHeader h;
    char cmd[512];
};

class NetServer
{
    public:
        typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

    public:
        NetServer(int portno);
        ~NetServer();

        void recv(NetServer::socket_ptr sock);
        void start();

    private:
        int m_portno;
        io_service m_service;
        ip::tcp::endpoint m_ep;
        ip::tcp::acceptor m_acc;
        int m_active;
};
