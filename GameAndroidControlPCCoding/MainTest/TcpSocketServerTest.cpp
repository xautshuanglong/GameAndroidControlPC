#include "stdafx.h"
#include "TcpSocketServerTest.h"

namespace Shuanglong::Test
{
    TcpSocketServerTest* TcpSocketServerTest::mpInstance = nullptr;

    TcpSocketServerTest::TcpSocketServerTest()
    {
    }

    TcpSocketServerTest::~TcpSocketServerTest()
    {
    }

    void TcpSocketServerTest::Entry()
    {
        mpInstance = new TcpSocketServerTest();
        mpInstance->mpLog = Log::GetInstance();

        std::cout << "---------------------------------- TcpSocketServerTest ----------------------------------" << std::endl;
    }
}

