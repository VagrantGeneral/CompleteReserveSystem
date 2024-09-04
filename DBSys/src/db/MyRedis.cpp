
#include "MyRedis.hpp"
#include "Logger.hpp"

namespace DB {
    MyRedis::MyRedis() : m_connect(nullptr)
                       , m_reply(nullptr)
                       , m_authreply(nullptr)
                       , m_pass("Itcast66^") {
        //create
        //
    }

    MyRedis::~MyRedis() {

    }

    bool MyRedis::connect(const std::string& host, int port) {
        this->m_connect = redisConnect(host.c_str(), port);
        if (m_connect == nullptr) {
            LOG_DEBUG << "Redis connect Failed!!!";
            return false;
        }

        if (this->m_connect->err) {
            LOG_DEBUG << "Redis connect Failed!!!" << m_connect->errstr;
            return false;
        }

        LOG_INFO << "Redis connect successful";
        return true;
    }
   
    bool MyRedis::isKeyCheck(const std::string& key) {
        m_reply = (redisReply*)redisCommand(m_connect, "exists %s", key.c_str());

        if (m_reply == nullptr || m_reply->integer == 0) {
            LOG_DEBUG << "isKeyCheck failed!!!";
            return false;
        }

        LOG_INFO << "EXIST SUCCESSFUL";
        freeReplyObject(m_reply);
        m_reply = nullptr;
        return true;
    }

    std::string MyRedis::get(const std::string& key) {
        m_reply = (redisReply*)redisCommand(m_connect, "get %s", key.c_str());

        if (m_reply == nullptr || m_reply->type == REDIS_ERR) {
            LOG_DEBUG << "get failed!!!";
            return std::string();
        }

        std::string str = m_reply->str;
        freeReplyObject(m_reply);
        m_reply = nullptr;

        return str;
    }

    bool MyRedis::set(const std::string& key, std::string& value) {
        m_reply = (redisReply*)redisCommand(m_connect, "set %s %s", key.c_str(), value.c_str());

        if (m_reply == nullptr || m_reply->type == REDIS_ERR) {
            LOG_DEBUG << "set failed!!!";
            return false;
        }
        LOG_INFO << "SET SUCCESSFUL";
        freeReplyObject(m_reply);
        m_reply = nullptr;
        return true;
    }


}