#pragma once

namespace Shuanglong
{
    namespace Test
    {
        class MySQLConnectionTest
        {
        private:

        public:
            ~MySQLConnectionTest();
            static MySQLConnectionTest* GetInstance();
            static void Entry();
            static void Exit();

        private:
            MySQLConnectionTest();
            void MysqlxBasedOperationTest();
        };
    }
}
