
#include "ProxyClient.hpp"

namespace DB {
    //std::unique_ptr<MySQLConn> mysql_conn;
    //std::string mysqlSer_Ip;
    //unsigned short mysqlSer_Port;   
    //std::string mysql_UserName;
    //std::string mysqlUserPasswd;
    //std::string dbName;

    ProxyClient::ProxyClient() 
        : mysqlSer_Ip("127.0.0.1")
        , mysqlSer_Port(3306)
        , mysqlUserName("root")
        , mysqlUserPasswd("Itcast66^")
        , dbName("GY2301") {
        //create//

    }

    ProxyClient::ProxyClient(const std::string& ip,
                             const unsigned short port,
                             const std::string& username,
                             const std::string& userpasswd,
                             const std::string& dbname) 
        : mysqlSer_Ip(ip)
        , mysqlSer_Port(port)
        , mysqlUserName(username)
        , mysqlUserPasswd(userpasswd)
        , dbName(dbname) {
        //create//

    }

    ProxyClient::~ProxyClient() {

    }

    bool ProxyClient::ConnectToMySQLSer() {
        mysql_conn.reset(new MySQLConn());
        return mysql_conn->InitConn(mysqlUserName, mysqlUserPasswd, dbName, mysqlSer_Ip, mysqlSer_Port);
    }

    bool ProxyClient::MySQL_TelRegister(const std::string& tel,
                                        const std::string& name,
                                        const std::string& pswd) {

    }

    bool ProxyClient::MySQL_Login(const std::string& tel, const std::string& pswd) {

    }






}