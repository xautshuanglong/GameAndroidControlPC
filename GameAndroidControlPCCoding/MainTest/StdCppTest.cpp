#include "stdafx.h"
#include "StdCppTest.h"

namespace Shuanglong::Test
{
#define DECLARE_SHARED_POINTER(clsName) typedef std::shared_ptr<clsName> Ptr##clsName;

    StdCppTest* StdCppTest::mpInstance = nullptr;

    StdCppTest::StdCppTest()
        : mpLog(nullptr)
    {
        printf_s("StdCppTest::StdCppTest() --\n");
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

        mpInstance->SharedPointerTypedefTest();
    }

    void StdCppTest::SharedPointerTypedefTest()
    {
        std::cout << "----------------------------- StdCppTest::SharedPointerTypedefTest() -----------------------------" << std::endl;

        std::shared_ptr<StdCppTest> ptrTest(new StdCppTest());
        ptrTest->SharedPointerHelperFunc();

        DECLARE_SHARED_POINTER(StdCppTest)
        PtrStdCppTest typedefTest(new StdCppTest);
        typedefTest->SharedPointerHelperFunc();
    }

    void StdCppTest::SharedPointerHelperFunc()
    {
        if (mpLog == nullptr)
        {
            mpLog = Log::GetInstance();
        }
        mpLog->Console(SL_CODELOCATION, "Enter function ----");
    }
}
