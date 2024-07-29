#ifndef MYREDIS_HPP
#define MYREDIS_HPP
#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include "Logger.hpp"

namespace DB {
    class MyRedis {
    private:
        redisContext* m_connect;

        redisReply* m_reply;

        redisReply* m_authreply;

        std::string m_pass;
        
    public:
        MyRedis();

        ~MyRedis();

        bool connect(const std::string& host, int port);

        bool isKeyCheck(const std::string& key);

        std::string get(const std::string& key);

        bool set(const std::string& key, std::string& value);

    };

}

  
#endif