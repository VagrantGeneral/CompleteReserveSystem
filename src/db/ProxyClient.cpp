
#include <sstream>
#include "ProxyClient.hpp"
#include "Logger.hpp"

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
        std::stringstream ss;
        ss << "insert into user_info value(0,";
        ss << "'" << tel << "',";
        ss << "'" << name << "',";
        ss << "'" << pswd << "',";
        ss << "CurDate());";
        LOG_INFO << ss.str();
        return mysql_conn->InsertSQL(ss.str());
    }

    LogInInFo ProxyClient::MySQL_Login(const std::string& tel, const std::string& pswd) {
        LogInInFo ret = {"", "", false};
        ret.tel = tel;
        std::stringstream ss;
        ss << "select Name, Passwd from user_info where Tel = '" << tel << "';";
        if (!mysql_conn->SelectSQL(ss.str())) {
            LOG_DEBUG << "Select failed";
            return ret;
        }
        if (!mysql_conn->GetRecordSet()) {
            LOG_DEBUG << "Null RecordSet";
            return ret;
        }
        int rownum = mysql_conn->GetRecordRows();
        if (rownum == 0) {
            LOG_DEBUG << "user name not find";
            return ret;
        }
        MYSQL_ROW row = mysql_conn->GetRecordToData();
        if (pswd.compare(row[1]) == 0) {
            ret.name = row[0];
            ret.tag = true;
        }
        mysql_conn->FreeRecordSet();
        return ret;
    }


}