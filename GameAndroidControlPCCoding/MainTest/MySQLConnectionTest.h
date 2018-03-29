#pragma once

namespace Shuanglong
{
    namespace Test
    {
        class MySQLConnectionTest
        {
        public:
            ~MySQLConnectionTest();
            static void Entry();
            static void Exit();

        private:
            MySQLConnectionTest();
        };
    }
}
