#ifndef PROXYCLIENT_HPP
#define PROXYCLIENT_HPP
#include <iostream>
#include <string>
#include <memory>
#include "MySQLConn.hpp"
#include "MyRedis.hpp"

namespace DB {
    struct LogInInFo {
        std::string tel;
        std::string name;
        bool tag;
    };

    class ProxyClient {
    private:
        std::unique_ptr<MySQLConn> mysql_conn;

        std::unique_ptr<MyRedis> myredis_conn;

    private:
        std::string mysqlSer_Ip;

        unsigned short mysqlSer_Port;

        std::string mysqlUserName;

        std::string mysqlUserPasswd;

        std::string dbName;

    private:
        std::string redis_Ip;

        int redis_Port;


    public:
        ProxyClient();

        ProxyClient(const std::string& ip,
                    const unsigned short port,
                    const std::string& username,
                    const std::string& userpasswd,
                    const std::string& dbname);

        ~ProxyClient();

        bool ConnectToMySQLSer();

        bool MySQL_TelRegister(const std::string& tel,
                               const std::string& name,
                               const std::string& pswd);

        LogInInFo MySQL_Login(const std::string& tel, const std::string& pswd);

        
        





    };
}

#endif