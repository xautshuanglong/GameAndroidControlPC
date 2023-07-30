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
        mpInstance = new StdCppTest();
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
        //printf_s("StdCppTest::StdCppTest() --\n");
    }

    StdCppTest::StdCppTest(const char* name)
        : mpLog(nullptr)
        , mpName(name)
    {
        //printf_s("StdCppTest::StdCppTest(const char* name) --\n");
    }

    StdCppTest::~StdCppTest()
    {
        //printf_s("StdCppTest::~StdCppTest() --\n");
    }

    void StdCppTest::Entry()
    {
        std::cout << "----------------------------- StdCpp Testing -----------------------------" << std::endl;
        mpInstance->mpLog = Log::GetInstance();

        //mpInstance->SharedPointerTypedefTest();
        //mpInstance->StdStringFormatTest();
        //mpInstance->NestedClassTest();
        //mpInstance->OperatorNewAndDelete();
        //mpInstance->PlacementNewTest();
        //mpInstance->UnionStructTest();
        mpInstance->RangeBasedForLoopTest();

        //mpInstance->StdAsyncFuturePromiseTest(mRetFuture);
        //mpInstance->mpLog->Console(SL_CODE_LOCATION, "After StdAsyncFuturePromiseTest finished");
    }

    void StdCppTest::StdStringFormatTest()
    {
        std::cout << "----------------------------- StdCppTest::StdStringFormatTest() -----------------------------" << std::endl;
        float floatX = (float)(1.0 / 3);
        double doubleX = 1.0 / 3;
        std::cout << "floatX:" << floatX << "  doubleX:" << doubleX << std::endl;
        printf_s("floatX:%.8f  doubleX:%.8f\n", floatX, doubleX);

        double pi = 3.1415926535898;
        std::cout << "std::cout << pi:" << pi << std::endl;
        std::cout << std::fixed << std::setprecision(15) << "cout << pi:" << pi << std::endl;
        printf_s("printf pi:%.15f\n", pi);
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
        mpLog->Console(SL_CODE_LOCATION, "Enter function <---- ClassName:%s", mpName);
    }

    void StdCppTest::StdAsyncFuturePromiseTest(std::future<int>& futureRes)
    {
        std::function<int(void)> asyncTestFunc = [this]()
        {
            int loopCount = 50;
            while (loopCount > 0)
            {
                --loopCount;
                mpLog->Console(SL_CODE_LOCATION, "loopCount=%d tid=%d", loopCount, std::this_thread::get_id());
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            return 666;
        };

        //// will block current thread
        //std::future_status status = std::future_status::timeout;
        //mpLog->Console(SL_CODE_LOCATION, "before async call...");
        //futureRes = std::async(std::launch::deferred, asyncTestFunc);
        //mpLog->Console(SL_CODE_LOCATION, "after async call...");
        //do
        //{
        //    //mpLog->Console(SL_CODE_LOCATION, "before futureRes.wait_for() valid=%s", StringUtil::BoolToString(futureRes.valid()).c_str());
        //    status = futureRes.wait_for(std::chrono::milliseconds(10));
        //    switch (status)
        //    {
        //    case std::future_status::ready:
        //        mpLog->Console(SL_CODE_LOCATION, "std::future_status::ready");
        //        break;
        //    case std::future_status::timeout:
        //        mpLog->Console(SL_CODE_LOCATION, "std::future_status::timeout");
        //        break;
        //    case std::future_status::deferred:
        //        mpLog->Console(SL_CODE_LOCATION, "std::future_status::deferred");
        //        //futureRes.get();  // 阻塞当前线程，返回异步执行结果，将导致 std::future 无效。
        //        //mpLog->Console(SL_CODE_LOCATION, "after futureRes.get()");
        //        futureRes.wait(); // 阻塞当前线程，等待异步完成。// Blocks the current thread until the associated asynchronous state is ready.
        //        mpLog->Console(SL_CODE_LOCATION, "after futureRes.wait()");
        //        break;
        //    default:
        //        break;
        //    }
        //} while (status != std::future_status::ready && futureRes.valid());

        futureRes = std::async(std::launch::async, asyncTestFunc);// 可能：内部 future 析构导致阻塞
    }

    void StdCppTest::NestedClassTest()
    {
        // inObj 没有父类，InnerClassFuncTest 内部操作将损坏堆栈（待验证）
        //OuterClass::InnerClass inObj;
        //inObj.InnerClassFuncTest();

        OuterClass outObj;
        outObj.OuterClassFuncTest();
        outObj.mOutPublicInnerObj.InnerClassFuncTest();
        outObj.OuterClassFuncTest();
    }

    void StdCppTest::OperatorNewAndDelete()
    {
        std::cout << "sizeof(OverloadNew) = " << sizeof(OverloadNew) << std::endl;

        OverloadNew overloadNewTest;
        OverloadNew *pOverloadNewTest = new OverloadNew();
        if (pOverloadNewTest != nullptr)
        {
            delete pOverloadNewTest;
        }

        OverloadNew *pOverloadNewWithStrTest = new(std::string("aaa")) OverloadNew(110);
        if (pOverloadNewWithStrTest != nullptr)
        {
            delete pOverloadNewWithStrTest;
        }

        // new[] 实际分配内存到底多大？
        OverloadNew *pOverloadArray1 = new OverloadNew[1];
        if (pOverloadArray1 != nullptr)
        {
            delete[] pOverloadArray1;
        }

        OverloadNew *pOverloadArray2 = new OverloadNew[2];
        if (pOverloadArray2 != nullptr)
        {
            delete[] pOverloadArray2;
        }

        OverloadNew *pOverloadArray3 = new OverloadNew[3];
        if (pOverloadArray3 != nullptr)
        {
            delete[] pOverloadArray3;
        }
    }

    void StdCppTest::PlacementNewTest()
    {
        char pBufferTest[128] = { 0 };
        std::cout << "_countof(pBufferTest) = " << _countof(pBufferTest) << std::endl;
        for (int i = 0; i < _countof(pBufferTest); ++i)
        {
            pBufferTest[i] = i;
        }

        OverloadNew *pOverloadNew = new(pBufferTest) OverloadNew();
        pOverloadNew->VirtualFuncTest();

        std::cout << "sizeof(PlacementNew)= " << sizeof(PlacementNew) << std::endl;
        PlacementNew  *pPlacementNewObj = new(pBufferTest+sizeof(OverloadNew)) PlacementNew();
        if (pPlacementNewObj != nullptr)
        {
            pPlacementNewObj->~PlacementNew();
        }
    }

    void StdCppTest::UnionStructTest()
    {
        union EndianTest
        {
            int intValue;
            char charValue[8]; // 占内存大小取决于 数组长度 并以 int 4字节对齐
        };

        std::cout << "sizeof(EndianTest) = " << sizeof(EndianTest) << std::endl;

        EndianTest endianObj;
        //endianObj.intValue = 0x00010203;
        endianObj.charValue[0] = 'A';
        endianObj.charValue[1] = 'B';
        endianObj.charValue[2] = 'C';
        endianObj.charValue[3] = '\0';

        std::ios::fmtflags oldFlags = std::cout.flags();
        std::cout << "EndianTest.intValue = 0x" << std::hex << std::setw(8) << std::setfill('0')
            << endianObj.intValue << std::endl
            << "EndianTest.charValue = " << endianObj.charValue << std::endl;

        std::cout.flags(oldFlags);
        std::cout << 16 << std::endl;
    }

    void StdCppTest::RangeBasedForLoopTest()
    {
        std::vector<int> a = { 9,8,7,6,5 };
        // 废弃
        //for each (int var1 in a)
        //{
        //    printf_s("var1 = %d\n", var1);
        //}
        for (int var2 : a)
        {
            printf_s("var2 = %d\n", var2);
        }

        printf_s("\n");

        int testArray[6] = { 1,2,3,4,5,6 };
        // 废弃
        //for each(int test1 in testArray)
        //{
        //    printf_s("test1 = %d\n", test1);
        //}
        for (int test2 : testArray)
        {
            printf_s("test2 = %d\n", test2);
        }
    }
}
