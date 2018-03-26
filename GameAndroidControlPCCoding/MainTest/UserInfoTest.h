#pragma once

namespace Shuanglong
{
    namespace Test
    {
        class UserInfoTest
        {
        private:

        public:
            ~UserInfoTest();
            static UserInfoTest* GetInstance();
            void Entry();
            void Exit();

        private:
            UserInfoTest();
            void MessageTestProto2Test();
        };
    }
}
