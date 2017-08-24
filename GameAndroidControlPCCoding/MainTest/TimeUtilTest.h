#pragma once
#include "Log.h"

namespace Shuanglong
{
    namespace Test
    {
        class TimeUtilTest sealed
        {
        private:
            TimeUtilTest();
            Log* mpLog = nullptr;

        public:
            ~TimeUtilTest();

            static TimeUtilTest *mpInstance;
            static void Entry();

            void TimeUtilTest_GetDateString();
            void TimeUtilTest_GetTimeString();
            void TimeUtilTest_GetDateTimeString();
            void TimeUtilTest_GetFormatTimeString();

            void TimeUtilTest_GetCurrentTimestamp();
            void TimeUtilTest_GetFullTimestampString();
            void TimeUtilTest_GetSimpleTimestampString();

            void TimeUtilTest_QueryPerformanceFrequency();
            void TimeUtilTest_QueryPerformanceCounter();

            void TimeUtilTest_TimeDiff();
        };
    }
}
