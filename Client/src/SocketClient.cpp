
#include "SocketClient.hpp"
#include "Logger.hpp"
#include <string.h>


namespace CLI {
    SocketClient::SocketClient(const std::string& sip, int sport) 
        : _fd(-1), ser_IP(sip), ser_PORT(sport) {
        //cerate

    }

    SocketClient::~SocketClient() {
        
    }

    
    bool SocketClient::connect() {
        _fd = socket(AF_INET, SOCK_STREAM, 0);
        if(-1 == _fd) {
            LOG_ERROR << "Socket Failed!!!";
            return false;
        }
        memset(&ser_addr, 0, sizeof(ser_addr));
        


    }

    int SocketClient::sendToServer(const std::string& str) {

    }

    std::string SocketClient::read() const {

    }


}