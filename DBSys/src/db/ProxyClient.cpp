
#include <sstream>
#include <jsoncpp/json/json.h>
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
        , dbName("GY2301")
        , redis_Ip("127.0.0.1")
        , redis_Port(6379) {
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

        //
        myredis_conn = std::make_unique<MyRedis>();
        if (!myredis_conn->connect(redis_Ip, redis_Port)) {
            LOG_DEBUG << "REDIS CONNECT FAILED!!!";
        }
        else {
            if (myredis_conn->isKeyCheck(ret.tel)) {
                std::string hrstr = myredis_conn->get(ret.tel);
                if (!hrstr.empty()) {
                    Json::Value val;
                    Json::Reader read;
                    read.parse(hrstr, val);
                    std::string rpsw = val["password"].asString();
                    if (rpsw.compare(pswd) == 0) {
                        ret.name = val["name"].asString();
                        ret.tag = true;
                        LOG_INFO << "LOGIN......REDIS";
                        return ret;
                    }
                }
            }
        }
        
        //
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
        if (ret.tag) {
            Json::Value user;
            user["name"] = ret.name;
            user["password"] = pswd;
            
            Json::FastWriter fw;
            std::string str = fw.write(user);

            std::stringstream ss;
            ss << "ex " << 30 * 60;
            LOG_INFO << "SET REDIS" << ret.tel << " " << str;
            str += ss.str();
            myredis_conn->set(ret.tel, str);
        }
        LOG_INFO << "LOGIN......MYSQL";
        return ret;
    }


}