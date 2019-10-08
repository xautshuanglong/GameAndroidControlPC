#pragma once

#include <Utils/SingletonUtil.h>

namespace Shuanglong::Test
{
    class RandomNumberTest : public Utils::SingletonUtil<RandomNumberTest>
    {
    public:
        ~RandomNumberTest();

    private:
        friend Utils::SingletonUtil<RandomNumberTest>;
        RandomNumberTest();
        void LinearCongruentialGeneratorTest();

    public:
        void Entry();
        void Exit();
    };
}
