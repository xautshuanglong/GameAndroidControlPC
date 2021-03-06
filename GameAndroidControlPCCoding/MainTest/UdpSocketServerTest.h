#pragma once

#include <thread>

#include "Log.h"
#include <SocketServer.h>

namespace Shuanglong::Test
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
        void Initialize();
        void StartListen();
        void StopListen();
        static void ListenThreadFunc(void *param);
    };
}

