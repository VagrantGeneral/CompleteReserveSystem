
#include "MySQLConn.hpp"
#include "Logger.hpp"

namespace DB {
    //MYSQL* m_sqlconn;//
    //MYSQL_RES* m_result;//
    //MYSQL_ROW* m_row;//


    bool MySQLConn::ExecuteSQL(const std::string& sqlstr) {
        bool res = true;
        if (mysql_real_query(m_sqlconn, sqlstr.c_str(), sqlstr.size()) != 0) {
            LOG_ERROR << "Can not execute " << mysql_error(m_sqlconn);
            res = false;
        }
        return res;
    }

    
    MySQLConn::MySQLConn()
        : m_sqlconn(nullptr)
        , m_result(nullptr)
        , m_row(nullptr) {
        //create
        if (mysql_library_init(0, nullptr, nullptr) != 0) {
            //failed
            LOG_FATAL << "mysql library init failed!!!";
        }
        if ((m_sqlconn  = mysql_init(nullptr)) == nullptr) {
            LOG_FATAL << "mysql init failed!!!";
        }
    }

    MySQLConn::MySQLConn(const std::string& user,
                         const std::string& psw,
                         const std::string& dbname,
                         const std::string& ip,
                         const unsigned short port) 
        : MySQLConn() {
        //create
        if (!InitConn(user, psw, dbname, ip, port)) {
            LOG_INFO << user << "," << psw << "," << dbname << "," << ip << "," << port;
            LOG_FATAL << "init conn failed";
        }
    }

    MySQLConn::~MySQLConn() {
        ExitConn();
        mysql_library_end();
    }

    void MySQLConn::ExitConn() {
        mysql_close(m_sqlconn);
        m_sqlconn = nullptr;
    }

    bool MySQLConn::InitConn(const std::string& user,
                             const std::string& psw,
                             const std::string& dbname,
                             const std::string& ip,
                             const unsigned short port) {
        bool res = true;
        if (nullptr == mysql_real_connect(m_sqlconn, ip.c_str(), user.c_str(), psw.c_str(), dbname.c_str(), port, nullptr, 0)) {
            LOG_DEBUG << "Failed to connect db " << dbname;
            LOG_ERROR << mysql_error(m_sqlconn);
            res = false;
        }
        return res;
    }

    bool MySQLConn::InsertSQL(const std::string& sqlstr) {
        bool res = true;
        int npa = sqlstr.find("insert");
        int npb = sqlstr.find("INSERT");
        if (npa == std::string::npos && npb == std::string::npos) {
            LOG_ERROR << "Not insert" << sqlstr;
            res = false;
        }
        if (res) {
            res = ExecuteSQL(sqlstr);
        }        
        return res;
    }

    bool MySQLConn::UpdateSQL(const std::string& sqlstr) {
        bool res = true;
        int npa = sqlstr.find("update");
        int npb = sqlstr.find("UPDATE");
        if (npa == std::string::npos && npb == std::string::npos) {
            LOG_ERROR << "Not update" << sqlstr;
            res = false;
        }
        if (res) {
            res = ExecuteSQL(sqlstr);
        }        
        return res;
    }

    bool MySQLConn::DeleteSQL(const std::string& sqlstr) {
        bool res = true;
        int npa = sqlstr.find("delete");
        int npb = sqlstr.find("DELETE");
        if (npa == std::string::npos && npb == std::string::npos) {
            LOG_ERROR << "Not delete" << sqlstr;
            res = false;
        }
        if (res) {
            res = ExecuteSQL(sqlstr);
        }        
        return res;
    }

    int MySQLConn::GetAffectedRow() const {
        return mysql_affected_rows(m_sqlconn);
    }


    bool MySQLConn::SelectSQL(const std::string& sqlstr) {
        bool res = true;
        int npa = sqlstr.find("select");
        int npb = sqlstr.find("SELECT");
        if (npa == std::string::npos && npb == std::string::npos) {
            LOG_ERROR << "Not select" << sqlstr;
            res = false;
        }
        if (res) {
            res = ExecuteSQL(sqlstr);
        }        
        return res;
    }

    bool MySQLConn::GetRecordSet() {
        bool res = true;
        m_result = mysql_store_result(m_sqlconn);
        if (nullptr == m_result) {
            LOG_DEBUG << "Get Recordset failed" << mysql_error(m_sqlconn);
            res = false;
        }
        return res;
    }

    int MySQLConn::GetRecordRows() const {
        return mysql_num_rows(m_result);
    }

    MYSQL_ROW MySQLConn::GetRecordToData() const {
        MYSQL_ROW newrow = mysql_fetch_row(m_result);
        if (newrow == nullptr) {
            LOG_DEBUG << "GetRecord Data failed" << mysql_error(m_sqlconn);

        }
        return newrow;
    }

    void MySQLConn::FreeRecordSet() {
        if (m_result != nullptr) {
            mysql_free_result(m_result);
        }
        m_result = nullptr;
    }


    bool MySQLConn::transaction() {
        return true;
    }

    bool MySQLConn::begin() {
        return mysql_query(m_sqlconn, "begin") == 0;
    }

    bool MySQLConn::commit() {
        return mysql_commit(m_sqlconn);
    }

    bool MySQLConn::rollback() {
        return mysql_rollback(m_sqlconn);
    }


}


