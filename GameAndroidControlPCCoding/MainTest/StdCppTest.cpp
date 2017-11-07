#include "stdafx.h"
#include "StdCppTest.h"

namespace Shuanglong::Test
{
    DECLARE_SHARED_POINTER(StdCppTest)

    StdCppTest* StdCppTest::mpInstance = nullptr;
    StdCppTest::SingleHelpper StdCppTest::mHelpper;
    std::future<int> StdCppTest::mRetFuture;

    StdCppTest::SingleHelpper::SingleHelpper()
    {
    }

    StdCppTest::SingleHelpper::~SingleHelpper()
    {
        if (mpInstance != nullptr)
        {
            delete mpInstance;
            mpInstance = nullptr;
        }
    }

    StdCppTest::StdCppTest()
        : mpLog(nullptr)
        , mpName(nullptr)
    {
        printf_s("StdCppTest::StdCppTest() --\n");
    }

    StdCppTest::StdCppTest(const char* name)
        : mpLog(nullptr)
        , mpName(name)
    {
        printf_s("StdCppTest::StdCppTest(const char* name) --\n");
    }

    StdCppTest::~StdCppTest()
    {
        printf_s("StdCppTest::~StdCppTest() --\n");
    }

    void StdCppTest::Entry()
    {
        std::cout << "----------------------------- StdCpp Testing -----------------------------" << std::endl;
        mpInstance = new StdCppTest();
        mpInstance->mpLog = Log::GetInstance();

        //mpInstance->SharedPointerTypedefTest();
        mpInstance->StdAsyncFuturePromiseTest(mRetFuture);
        mpInstance->mpLog->Console(SL_CODELOCATION, "After StdAsyncFuturePromiseTest finished");
    }

    void StdCppTest::SharedPointerTypedefTest()
    {
        std::cout << "----------------------------- StdCppTest::SharedPointerTypedefTest() -----------------------------" << std::endl;

        std::shared_ptr<StdCppTest> ptrTest(new StdCppTest("std::shared_ptr<StdCppTest>"));
        ptrTest->SharedPointerHelperFunc();

        PtrStdCppTest typedefTest(new StdCppTest("PtrStdCppTest"));
        typedefTest->SharedPointerHelperFunc();
    }

    void StdCppTest::SharedPointerHelperFunc()
    {
        if (mpLog == nullptr)
        {
            mpLog = Log::GetInstance();
        }
        mpLog->Console(SL_CODELOCATION, "Enter function <---- ClassName:%s", mpName);
    }

    void StdCppTest::StdAsyncFuturePromiseTest(std::future<int>& futureRes)
    {
        std::function<int(void)> asyncTestFunc = [this]()
        {
            int loopCount = 50;
            while (loopCount > 0)
            {
                --loopCount;
                mpLog->Console(SL_CODELOCATION, "loopCount=%d tid=%d", loopCount, std::this_thread::get_id());
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            return 666;
        };

        std::future_status status;
        mpLog->Console(SL_CODELOCATION, "before async call...");
        futureRes = std::async(std::launch::deferred, asyncTestFunc);
        mpLog->Console(SL_CODELOCATION, "after async call...");
        do
        {
            mpLog->Console(SL_CODELOCATION, "before futureRes.wait_for() valid=%s", StringUtil::BoolToString(futureRes.valid()).c_str());
            status = futureRes.wait_for(std::chrono::milliseconds(10));
            switch (status)
            {
            case std::future_status::ready:
                mpLog->Console(SL_CODELOCATION, "std::future_status::ready");
                break;
            case std::future_status::timeout:
                mpLog->Console(SL_CODELOCATION, "std::future_status::timeout");
                break;
            case std::future_status::deferred:
                mpLog->Console(SL_CODELOCATION, "std::future_status::deferred");
                //futureRes.get();  // 阻塞当前线程，返回异步执行结果，将导致 std::future 无效。
                //mpLog->Console(SL_CODELOCATION, "after futureRes.get()");
                futureRes.wait(); // 阻塞当前线程，等待异步完成。// Blocks the current thread until the associated asynchronous state is ready.
                mpLog->Console(SL_CODELOCATION, "after futureRes.wait()");
                break;
            default:
                break;
            }
        } while (status != std::future_status::ready && futureRes.valid());

        //std::async(std::launch::async, asyncTestFunc);// 可能：内部 future 析构导致阻塞
    }
}
