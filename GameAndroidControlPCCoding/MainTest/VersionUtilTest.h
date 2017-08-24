#pragma once

#include "Log.h"

namespace Shuanglong
{
    namespace Test
    {
        class VersionUtilTest sealed
        {
        private:
            Log                     *mpLog;
            static VersionUtilTest  *mpInstance;
            VersionUtilTest();

        public:
            ~VersionUtilTest();

            static void Entry();

            void GetFileVersionInfoTest();
        };
    }
}

