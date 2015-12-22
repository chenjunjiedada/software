#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

struct NetCmdHeader
{
    uint16_t type;
    uint16_t length;
    uint32_t crc;
};

struct NetCmd 
{
    NetCmdHeader h;
    char cmd[512];
};


void print(const boost::system::error_code&) 
{
    std::cout << "timeout" << std::endl;
}

void starttimer(int delay) 
{
    boost::asio::io_service io;
    boost::asio::deadline_timer timer(io);
    timer.expires_from_now(boost::posix_time::seconds(delay));
    timer.async_wait(&print);
    io.run();
}

int main(int argc, char* argv[]) 
{
    int sockfd, port;

    struct sockaddr_in server_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if ((server = gethostbyname("localhost")) == NULL) 
    {
        std::cout << "failed to get hostname" << std::endl;
    }

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&server_addr.sin_addr.s_addr,
          server->h_length);

    server_addr.sin_port = htons(9999);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cout << "failed to connect to server" << std::endl;
        close(sockfd);
        return -1;
    }

    char term[] = "\r\n";

    char ack[3] = {0,0,0};


    while(true)
    {
        boost::thread t(starttimer, 10);
        NetCmd nc;
        memset(nc.cmd, 0, 512);
        std::cin.getline(nc.cmd, 512);
        nc.h.type = 1;
        nc.h.length = std::cin.gcount() + sizeof(nc.h);

        // Send cmd;
        write(sockfd, &nc, nc.h.length);

        // Send Terminator
        write(sockfd, term, sizeof(term));

        read(sockfd, ack, 3);

        std::cout << ack << std::endl;
        t.join();
    }

    
    close(sockfd);

    return 0;
}
