#pragma once

#include "Log.h"

namespace ShuangLong
{
    namespace Test
    {
        class TcpSocketServerTest
        {
        private:
            Log                         *mpLog;
            static TcpSocketServerTest  *mpInstance;
            TcpSocketServerTest();

        public:
            ~TcpSocketServerTest();
            static void Entry();
        };
    }
}

