#pragma once

#include <thread>

#include "Log.h"
#include <SocketServer.h>

namespace ShuangLong
{
    namespace Test
    {
        class UdpSocketServerTest
        {
        private:
            Log                             *mpLog;
            Socket::SocketServer             mLogServer;
            std::thread                     *mpListenThread;
            volatile bool                    mListenRuningFlag;
            static UdpSocketServerTest      *mpInstance;

        public:
            ~UdpSocketServerTest();
            static void Entry();
            static void Exit();

        private:
            UdpSocketServerTest();
            void StartListen();
            void StopListen();
            static void ListenThreadFunc(void *param);
        };
    }
}

