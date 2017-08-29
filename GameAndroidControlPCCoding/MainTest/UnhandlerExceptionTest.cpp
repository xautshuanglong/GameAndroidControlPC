#include "stdafx.h"
#include "UnhandlerExceptionTest.h"

namespace Shuanglong::Test
{
    std::atomic<UnhandlerExceptionTest*>     UnhandlerExceptionTest::mpInstance = nullptr;
    std::mutex                               UnhandlerExceptionTest::mMutexInstance;
    UnhandlerExceptionTest::DestructHellpper UnhandlerExceptionTest::mDestructHellper;

    UnhandlerExceptionTest::UnhandlerExceptionTest()
    {
        std::cout << "UnhandlerExceptionTest::UnhandlerExceptionTest()" << std::endl;
    }

    UnhandlerExceptionTest::~UnhandlerExceptionTest()
    {
        std::cout << "UnhandlerExceptionTest::~UnhandlerExceptionTest()" << std::endl;
    }

    UnhandlerExceptionTest* UnhandlerExceptionTest::GetInstance()
    {
        UnhandlerExceptionTest *pTemp = mpInstance.load(std::memory_order_acquire);

        if (pTemp == nullptr)
        {
            std::lock_guard<std::mutex> lock(mMutexInstance);
            if (pTemp == nullptr)
            {
                pTemp = new UnhandlerExceptionTest();
                mpInstance.store(pTemp, std::memory_order_release);
            }
        }

        return pTemp;
    }

    void UnhandlerExceptionTest::InitializeHandler()
    {
        //::SetUnhandledExceptionFilter();
    }

    void UnhandlerExceptionTest::UninitializeHandler()
    {
        ;
    }
}
