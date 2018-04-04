#include "stdafx.h"
#include "MySQLConnectionTest.h"

#include <mysqlx/xdevapi.h>

#include <Utils/StringUtil.h>

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

        try
        {
            mysqlx::Session sqlSession(
                mysqlx::SessionOption::USER, "shuanglong",
                mysqlx::SessionOption::PWD, "shuanglong123456",
                mysqlx::SessionOption::HOST, "192.168.0.84",
                mysqlx::SessionOption::PORT, 33070,
                mysqlx::SessionOption::SSL_MODE, mysqlx::SSLMode::DISABLED
            );

            mysqlx::Schema schema = sqlSession.getSchema("shuanglongtest");
            std::vector<std::string> tableNames = schema.getTableNames();
            std::cout << "size=" << tableNames.size() << std::endl;
            for (auto tableName : tableNames)
            {
                std::cout << "table name: " << tableName << std::endl;
            }

            mysqlx::Table tbStudents = schema.getTable("students");
            std::cout << "Table element count: " << tbStudents.count() << std::endl;

            mysqlx::RowResult result = tbStudents.select("*").execute();
            std::vector<mysqlx::Row> rowVector = result.fetchAll();

            int id = 0;
            int age = 0;
            std::string nameStr("");
            mysqlx::Value stuNameValue;

            std::cout << "Row count = " << rowVector[0].colCount() << std::endl;
            for (auto row : rowVector)
            {
                id = row.get(0);
                age = row.get(2);
                stuNameValue = row.get(1);
                std::cout << "id: " << id
                    << "   name: " << nameStr
                    << "age: " << age << std::endl;
            }

        }
        catch (const mysqlx::Error &err)
        {
            std::cout << "Mysql error: " << err << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << "STD Exception: " << e.what() << std::endl;
        }
        catch (const char* e)
        {
            std::cout << "Exception: " << e << std::endl;
        }

    }

    void MySQLConnectionTest::Exit()
    {
    }
}
