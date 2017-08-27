#include "stdafx.h"
#include "StdCppTest.h"

namespace Shuanglong::Test
{
    DECLARE_SHARED_POINTER(StdCppTest)

    StdCppTest* StdCppTest::mpInstance = nullptr;
    StdCppTest::SingleHelpper StdCppTest::mHelpper;

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

        mpInstance->SharedPointerTypedefTest();
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
}
