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

    MySQLConnectionTest* MySQLConnectionTest::GetInstance()
    {
        static MySQLConnectionTest instance;
        return &instance;
    }
 
    void MySQLConnectionTest::Entry()
    {
        std::cout << "----------------------------- Mysql Connection Testing -----------------------------" << std::endl;
        //GetInstance()->MysqlxBasedOperationTest();
    }

    void MySQLConnectionTest::Exit()
    {
    }

    void MySQLConnectionTest::MysqlxBasedOperationTest()
    {
        try
        {
            mysqlx::Session sqlSession(
                mysqlx::SessionOption::USER, "shuanglong",
                mysqlx::SessionOption::PWD, "shuanglong123456",
                mysqlx::SessionOption::HOST, "192.168.0.94",
                mysqlx::SessionOption::PORT, 33070,
                mysqlx::SessionOption::SSL_MODE, mysqlx::SSLMode::DISABLED
            );

            mysqlx::Schema schema = sqlSession.getSchema("shuanglong");
            std::vector<std::string> tableNames = schema.getTableNames();
            std::cout << "size=" << tableNames.size() << std::endl;
            for (auto tableName : tableNames)
            {
                std::cout << "table name: " << tableName << std::endl;
            }

            mysqlx::Table tbStudents = schema.getTable("students");
            std::cout << "Table element count: " << tbStudents.count() << std::endl;

            //tbStudents.insert("id", "name", "age").values(0, "hehe", 110).execute();
            mysqlx::RowResult result = tbStudents.select("*").execute();
            //sqlSession.sql("insert into shuanglong.students values(0, 'en', 99)").execute();
            //mysqlx::RowResult result = sqlSession.sql("select * from shuanglong.students").execute();
            std::vector<mysqlx::Row> rowVector = result.fetchAll();

            int id = 0;
            int age = 0;
            std::string nameStr;

            std::cout << "Row count = " << rowVector[0].colCount() << std::endl;
            for (auto row : rowVector)
            {
                id = row.get(0);
                nameStr = row.get(1);
                age = row.get(2);
                std::cout << "id: " << id
                    << "   name: " << nameStr
                    << "    age: " << age << std::endl;
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
}
