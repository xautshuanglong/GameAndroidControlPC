#include "stdafx.h"
#include "MultiThreadTest.h"

#include "Log.h"

namespace Shuanglong::Test
{
    MultiThreadTest* MultiThreadTest::mpInstance = nullptr;
    MultiThreadTest::SingleHelpper MultiThreadTest::mHelpper;

    // ÷∏’Î Õ∑≈∏®÷˙¿‡
    MultiThreadTest::SingleHelpper::SingleHelpper()
    {
        mpInstance = new MultiThreadTest();
    }

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

    MultiThreadTest* MultiThreadTest::GetInstance()
    {
        return mpInstance;
    }

    void MultiThreadTest::Entry()
    {
        std::cout << "----------------------------- MultiThreadTest -----------------------------" << std::endl;

        mpInstance->mpLog = Log::GetInstance();
    }
}
