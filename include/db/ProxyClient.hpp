#ifndef PROXYCLIENT_HPP
#define PROXYCLIENT_HPP
#include <iostream>
#include <string>
#include <memory>
#include "MySQLConn.hpp"

namespace DB {
    class ProxyClient {
    private:
        std::unique_ptr<MySQLConn> mysql_conn;

    private:
        std::string mysqlSer_Ip;

        unsigned short mysqlSer_Port;

        std::string mysqlUserName;

        std::string mysqlUserPasswd;

        std::string dbName;


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

        bool MySQL_Login(const std::string& tel, const std::string& pswd);

        






    };
}

#endif