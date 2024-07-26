#ifndef MYSQLCONN_HPP
#define MYSQLCONN_HPP
#include <iostream>
#include <string>
#include <mysql/mysql.h>

namespace DB {
    class MySQLConn {
    private:
        MYSQL* m_sqlconn;//

        MYSQL_RES* m_result;//

        MYSQL_ROW* m_row;//

    protected:
        bool ExecuteSQL(const std::string& sqlstr);

    public:
        MySQLConn();

        MySQLConn(const std::string& user,
                  const std::string& psw,
                  const std::string& dbname,
                  const std::string& ip,
                  const unsigned short port = 3306);

        ~MySQLConn();

        void ExitConn();

        bool InitConn(const std::string& user,
                      const std::string& psw,
                      const std::string& dbname,
                      const std::string& ip,
                      const unsigned short port = 3306);

        bool InsertSQL(const std::string& sqlstr);

        bool UpdateSQL(const std::string& sqlstr);

        bool DeleteSQL(const std::string& sqlstr);

        int GetAffectedRow() const;


        bool SelectSQL(const std::string& sqlstr);

        bool GetRecordSet();

        int GetRecordRows() const;

        MYSQL_ROW GetRecordToData() const;

        void FreeRecordSet();


        bool transaction();

        bool begin();

        bool commit();

        bool rollback();

    };


}

#endif