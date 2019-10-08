#include "RandomNumberTest.h"

#include <iostream>

namespace Shuanglong::Test
{
    RandomNumberTest::RandomNumberTest()
    {
    }

    RandomNumberTest::~RandomNumberTest()
    {
    }

    void RandomNumberTest::Entry()
    {
        std::cout << "void RandomNumberTest::Entry()" << std::endl;
        this->LinearCongruentialGeneratorTest();
    }

    void RandomNumberTest::Exit()
    {
        std::cout << "void RandomNumberTest::Exit()" << std::endl;
    }

    void RandomNumberTest::LinearCongruentialGeneratorTest()
    {
        for (int i = 0; i < 100; ++i)
        {
            if (i + 1 % 10 == 0)
            {
                std::cout << std::endl;
            }
            std::cout.width(10);
            std::cout << rand(); //std::cout << i;
        }

        std::cout << std::endl << std::endl;

        for (int i = 0; i < 100; ++i)
        {
            if (i + 1 % 10 == 0)
            {
                std::cout << std::endl;
            }
            std::cout.width(10);
            std::cout << rand(); //std::cout << i;
        }
    }
}
