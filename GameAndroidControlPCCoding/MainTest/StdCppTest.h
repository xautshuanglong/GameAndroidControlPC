#pragma once

#include "Log.h"

namespace Shuanglong::Test
{
    class StdCppTest sealed
    {
    private:
        StdCppTest();
        Log*                    mpLog;
        static StdCppTest   *mpInstance;

    public:
        ~StdCppTest();
        static void Entry();
    };
}

