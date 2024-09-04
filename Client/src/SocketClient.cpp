
#include "SocketClient.hpp"
#include "Logger.hpp"
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <string>


namespace CLI {
    SocketClient::SocketClient(const std::string& sip, int sport) 
        : _fd(-1), ser_IP(sip), ser_PORT(sport), ser_addr{} {
        //cerate

    }

    SocketClient::~SocketClient() {
        close(_fd);
        _fd = -1;
    }

    
    bool SocketClient::Connect() {
        _fd = socket(AF_INET, SOCK_STREAM, 0);
        if(-1 == _fd) {
            LOG_ERROR << "Socket Failed!!!";
            return false;
        }
        memset(&ser_addr, 0, sizeof(ser_addr));
        
        ser_addr.sin_family = AF_INET;
        ser_addr.sin_port = htons(ser_PORT);
        ser_addr.sin_addr.s_addr = inet_addr(ser_IP.c_str());

        int res = ::connect(_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
        if (res == -1) {
            LOG_ERROR << "Connect Failed!!!";
            return false;
        }
        return true;
    }

    int SocketClient::SendToServer(const std::string& str) {
        int n = ::send(_fd, str.c_str(), str.size(), 0);
        if (n < 0) {
            LOG_DEBUG << "Send Failed!!!" << strerror(n);
            return -1;
        }
        return n;
    } 

    std::string SocketClient::ReadFromServer() const {
        const int slen = 1024 * 10;
        char buff[slen] = {};
        int n = ::recv(_fd, buff, slen - 1, 0);
        if(n <= 0) {
            LOG_ERROR << "Server Close!!!";
            return std::string();
        }
        return std::string(buff);
    }


}