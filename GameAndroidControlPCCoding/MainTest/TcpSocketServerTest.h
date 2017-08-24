#pragma once

#include "Log.h"

namespace Shuanglong::Test
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
