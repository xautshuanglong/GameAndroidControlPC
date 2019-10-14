#include "stdafx.h"
#include "MultiThreadTest.h"

#include "Log.h"

namespace Shuanglong::Test
{
    MultiThreadTest* MultiThreadTest::mpInstance = nullptr;
    MultiThreadTest::SingleHelpper MultiThreadTest::mHelpper;

    int MultiThreadTest::mgCountCommon = 100;
    std::atomic<int> MultiThreadTest::mgCountAtomic = 100;

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

        //this->ThreadCommon_Test();
        this->ThreadAtomic_Test();
    }

    void MultiThreadTest::ThreadCommon_Test()
    {
        std::thread thread_test_1(ThreadFunc_Common);
        std::thread thread_test_2(ThreadFunc_Common);
        std::thread thread_test_3(ThreadFunc_Common);

        mpLog->Console(SL_CODE_LOCATION, "After construct thread common : %u", thread_test_1.get_id());
        mpLog->Console(SL_CODE_LOCATION, "After construct thread common : %u", thread_test_2.get_id());
        mpLog->Console(SL_CODE_LOCATION, "After construct thread common : %u", thread_test_3.get_id());

        thread_test_1.join();
        thread_test_2.join();
        thread_test_3.join();
    }

    void MultiThreadTest::ThreadAtomic_Test()
    {
        std::thread thread_test_1(ThreadFunc_Atomic);
        std::thread thread_test_2(ThreadFunc_Atomic);
        std::thread thread_test_3(ThreadFunc_Atomic);

        mpLog->Console(SL_CODE_LOCATION, "After construct thread atomic : %u", thread_test_1.get_id());
        mpLog->Console(SL_CODE_LOCATION, "After construct thread atomic : %u", thread_test_2.get_id());
        mpLog->Console(SL_CODE_LOCATION, "After construct thread atomic : %u", thread_test_3.get_id());

        thread_test_1.join();
        thread_test_2.join();
        thread_test_3.join();
    }

    void MultiThreadTest::ThreadFunc_Common()
    {
        do 
        {
            mpInstance->mpLog->Console(SL_CODE_LOCATION, "ThreadID: %u --> %d", std::this_thread::get_id(), mgCountCommon);
            --mgCountCommon;
        } while (mgCountCommon > 0);
    }

    void MultiThreadTest::ThreadFunc_Atomic()
    {
        do
        {
            int countAtomic = mgCountAtomic.load(std::memory_order_acquire);
            if (mgCountAtomic.compare_exchange_strong(countAtomic, countAtomic-1, std::memory_order_acquire))
            {
                mpInstance->mpLog->Console(SL_CODE_LOCATION, "ThreadID: %u --> %d succeed", std::this_thread::get_id(), countAtomic);
            }
            else
            {
                mpInstance->mpLog->Console(SL_CODE_LOCATION, "ThreadID: %u --> %d Failed", std::this_thread::get_id(), countAtomic);
            }
        } while (mgCountAtomic.load(std::memory_order_acquire) > 0);
    }
}
