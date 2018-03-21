#pragma once

#include "Log.h"

namespace Shuanglong
{
    namespace Test
    {
        class LibcurlHttpTest
        {
        private:
            Log*             mpLog;

        public:
            ~LibcurlHttpTest();
            static LibcurlHttpTest* GetInstance();
            void Entry();
            void Exit();

        private:
            LibcurlHttpTest();
            void CurlHttpGetTest();
        };
    }
}
