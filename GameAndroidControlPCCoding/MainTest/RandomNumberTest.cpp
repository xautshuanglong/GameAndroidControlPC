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
        //this->LinearCongruentialGeneratorTest();
    }

    void RandomNumberTest::Exit()
    {
        std::cout << "void RandomNumberTest::Exit()" << std::endl;
    }

    void RandomNumberTest::LinearCongruentialGeneratorTest()
    {
        srand(1);
        for (int i = 0; i < 100; ++i)
        {
            std::cout.width(10);
            std::cout << rand();
            //std::cout << i;
            if ((i + 1) % 10 == 0)
            {
                std::cout << std::endl;
            }
        }

        std::cout << std::endl << std::endl;

        srand(1);
        for (int i = 0; i < 100; ++i)
        {
            std::cout.width(10);
            std::cout << rand();
            //std::cout << i;
            if ((i + 1) % 10 == 0)
            {
                std::cout << std::endl;
            }
        }

        std::cout << std::endl << std::endl;
    }
}
