#pragma once

#include <TestClass.h>

namespace Shuanglong
{
    class TestClassTest sealed
    {
    private:
        TestClassTest();
        TestClass *mpTestClass;
        static TestClassTest *mpInstance;

    public:
        ~TestClassTest();

        static void Entry();

        void TestMethodTest();
    };
}
