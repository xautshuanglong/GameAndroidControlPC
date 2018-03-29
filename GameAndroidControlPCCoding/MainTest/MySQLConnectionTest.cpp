#include "stdafx.h"
#include "MySQLConnectionTest.h"

#include <mysql/mysql_driver.h>
#include <mysql/mysql_connection.h>
#include <mysql/cppconn/statement.h>

#include "Log.h"

namespace Shuanglong::Test
{
    MySQLConnectionTest::MySQLConnectionTest()
    {}

    MySQLConnectionTest::~MySQLConnectionTest()
    {}

    void MySQLConnectionTest::Entry()
    {
        std::cout << "----------------------------- Mysql Connection Testing -----------------------------" << std::endl;

        sql::mysql::MySQL_Driver *pDriver = nullptr;
        sql::Connection *pConn = nullptr;
        sql::Statement *pStatement = nullptr;
        sql::ResultSet *pResultSet = nullptr;

        pDriver = sql::mysql::get_mysql_driver_instance();
        pConn = pDriver->connect("tcp://192.168.0.84:3307", "shuanglong", "shuanglong123456");

        int on_off = 1;
        if (pConn->isValid())
        {
            Log::GetInstance()->Console(SL_CODE_LOCATION, "Connect mysql successfully!");
            pConn->setClientOption("clientTrace", &on_off);
            pStatement = pConn->createStatement();
            pStatement->execute("use shuanglongtest");
            //pStatement->execute("insert into student(name, age) VALUES ('MysqlTest', 11)");

            int id = 0;
            int age = 0;
            sql::SQLString name;

            pResultSet = pStatement->executeQuery("select id,name,age from student");
            while (pResultSet->next())
            {
                id = pResultSet->getInt(1);
                name = pResultSet->getString(2);
                age = pResultSet->getInt(3);
                std::cout << "id:" << id << std::setw(10)
                    << "name:" << name.c_str() << std::setw(10)
                    << "age:" << age << std::endl;
            }
        }

        delete pResultSet;
        delete pStatement;
        delete pConn;
    }

    void MySQLConnectionTest::Exit()
    {
    }
}
