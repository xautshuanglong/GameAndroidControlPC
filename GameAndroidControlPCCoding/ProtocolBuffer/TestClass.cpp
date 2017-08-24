#include "stdafx.h"
#include "TestClass.h"

namespace Shuanglong
{
    TestClass::TestClass()
    {
        std::cout << "TestClass.cpp TestClass::TestClass()" << std::endl;
    }

    TestClass::~TestClass()
    {
        std::cout << "TestClass.cpp TestClass::~TestClass()" << std::endl;
    }

    void TestClass::TestMethod()
    {
        std::cout << "TestClass.cpp TestClass::TestMethod()" << std::endl;
    }
}
