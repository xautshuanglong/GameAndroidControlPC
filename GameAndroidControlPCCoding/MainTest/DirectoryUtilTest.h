#pragma once

#include "Log.h"

namespace Shuanglong::Test
{
    class DirectoryUtilTest sealed
    {
    private:
        DirectoryUtilTest();
        Log* mpLog = nullptr;

    public:
        ~DirectoryUtilTest();

        static DirectoryUtilTest *mpInstance;
        static void Entry();
        static void Exit();

        void DirectoryUtilTest_Try();
        void DirectoryUtilTest_GetEnv();
    };
}
