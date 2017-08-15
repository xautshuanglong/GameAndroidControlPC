#include "stdafx.h"
#include "TcpSocketServerTest.h"

namespace ShuangLong::Test
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

        mpInstance->mpLog->Console(SL_CODELOCATION, "Enter function ------------");
    }
}

