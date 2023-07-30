#pragma once

#include "Log.h"

namespace Shuanglong::Test
{
    class UpPrivilegeTest sealed
    {
    private:
        UpPrivilegeTest();
        Log* mpLog = nullptr;

    public:
        ~UpPrivilegeTest();

        static UpPrivilegeTest *mpInstance;
        static void Entry();

        bool IsOsVersionVistaOrGreater();
        void ShellExecuteExOpen(LPCWSTR appName, LPCWSTR appPath);
    };
}
