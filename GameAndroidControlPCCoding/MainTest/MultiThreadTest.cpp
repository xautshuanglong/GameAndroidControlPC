#include "stdafx.h"
#include "MultiThreadTest.h"

#include "Log.h"

namespace Shuanglong::Test
{
    MultiThreadTest* MultiThreadTest::mpInstance = nullptr;
    MultiThreadTest::SingleHelpper MultiThreadTest::mHelpper;

    // ÷∏’Î Õ∑≈∏®÷˙¿‡
    MultiThreadTest::SingleHelpper::SingleHelpper()
    {}

    MultiThreadTest::SingleHelpper::~SingleHelpper()
    {
        if (mpInstance != nullptr)
        {
            delete mpInstance;
            mpInstance = nullptr;
        }
    }

    MultiThreadTest::MultiThreadTest()
    {}

    MultiThreadTest::~MultiThreadTest()
    {}

    void MultiThreadTest::Entry()
    {
        std::cout << "----------------------------- MultiThreadTest -----------------------------" << std::endl;
        mpInstance = new MultiThreadTest();
        mpInstance->mpLog = Log::GetInstance();
    }
}
