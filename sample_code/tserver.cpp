#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ts_net_server.h"


int main(int argc, char* argv[]) 
{
    /*
    struct sockaddr_in socket_info;

    struct hostent *host;

    int socket_handler;

    if ((socket_handler = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "failed to create socket\n";
        close(socket_handler);
    }

    socket_info.sin_family = AF_INET;
    socket_info.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_info.sin_port = htons(9999);

    if (bind(socket_handler, (struct sockaddr *)&socket_info, sizeof(socket_info)) < 0)
    {
        std::cout << "failed to bind to localhost\n";
        close(socket_handler);
    }

    listen(socket_handler, 5);

//    while(1) 
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int connection;
        if ((connection = accept(socket_handler, (struct sockaddr *)&client_addr, &client_len)) < 0)
        {
            std::cout << "failed on accept\n";
            close(socket_handler);
            return -1;
        }

        std::cout << "Server: got connection from:" << inet_ntoa(client_addr.sin_addr) 
            << " port: " << ntohs(client_addr.sin_port) << std::endl;
        
        uint8_t *data = new uint8_t[255];
        int bytes = read(connection, data, 255);
       
        if (bytes >= 0)
        {
            std::cout << "recv " << bytes << " bytes data\n";
            std::cout << (char*)data << std::endl;
        }
        else {
            std::cout << "failed to receive data from client\n";
        }


        write(connection, "world\n", 5);

        close(connection);
    }

    close(socket_handler);
    */

    NetServer ns(9999);
    ns.start();

    return 0;
}
