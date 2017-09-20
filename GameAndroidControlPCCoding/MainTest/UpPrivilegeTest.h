#pragma once

#include "Log.h"

namespace Shuanglong
{
    namespace Test
    {
        class UpPrivilegeTest sealed
        {
        private:
            UpPrivilegeTest();
            Log* mpLog;

        public:
            ~UpPrivilegeTest();

            static UpPrivilegeTest *mpInstance;
            static void Entry();

            bool IsOsVersionVistaOrGreater();
            void ShellExecuteExOpen(LPWSTR appName, LPWSTR appPath);
        };
    }
}

