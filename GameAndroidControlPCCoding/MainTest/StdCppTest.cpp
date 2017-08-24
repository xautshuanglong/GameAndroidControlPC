#include "stdafx.h"
#include "StdCppTest.h"

namespace Shuanglong::Test
{
    StdCppTest* StdCppTest::mpInstance = nullptr;

    StdCppTest::StdCppTest()
    {}

    StdCppTest::~StdCppTest()
    {}

    void StdCppTest::Entry()
    {
        std::cout << "----------------------------- StdCpp Testing -----------------------------" << std::endl;
        mpInstance = new StdCppTest();
        mpInstance->mpLog = Log::GetInstance();
    }
}
