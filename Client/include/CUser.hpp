#ifndef CUSER_HPP
#define CUSER_HPP
#include <string>
#include <memory>
#include "SocketClient.hpp"

namespace CLI{
    class CUser {
    private:
        std::unique_ptr<CLI::SocketClient> client;

    private:
        std::string name_;
        std::string tel_;

        int tagReg_;
        int tagLogIn_;
        int tagConn_;

    public:
        bool IsRegister() const { 
            return tagReg_ == 1; 
        }

        bool IsLogIn() const { 
            return tagLogIn_ == 1; 
        }


    public:
        CUser();

        ~CUser();

        bool ConnectToSer(const std::string &ip = "127.0.0.1", const int port = 8080);

        int Register(const std::string &name, const std::string &pws, const std::string &tel);

        int LogIn(const std::string &tel, const std::string &pws);

    };

}

#endif
