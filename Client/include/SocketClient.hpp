#ifndef SOCKETCLIENT_HPP
#define SOCKETCLIENT_HPP
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>



namespace CLI {
    class SocketClient {
    private:
        int _fd;

        std::string ser_IP;

        int ser_PORT;

        sockaddr_in ser_addr;

    public:
        SocketClient(const std::string& sip, int sport);

        ~SocketClient();

    public:
        bool connect();

        int sendToServer(const std::string& str);

        std::string read() const;


    };
}



#endif