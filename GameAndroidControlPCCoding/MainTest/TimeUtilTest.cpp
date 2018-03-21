#include "stdafx.h"
#include "TimeUtilTest.h"

namespace Shuanglong::Test
{
    TimeUtilTest* TimeUtilTest::mpInstance = nullptr;

    TimeUtilTest::TimeUtilTest()
    {
        ;
    }

    TimeUtilTest::~TimeUtilTest()
    {
        ;
    }

    void TimeUtilTest::Entry()
    {
        mpInstance = new TimeUtilTest();
        mpInstance->mpLog = Log::GetInstance();

        mpInstance->TimeUtilTest_GetDateString();
        mpInstance->TimeUtilTest_GetTimeString();
        mpInstance->TimeUtilTest_GetDateTimeString();
        mpInstance->TimeUtilTest_GetFormatTimeString();

        mpInstance->TimeUtilTest_GetCurrentTimestamp();
        mpInstance->TimeUtilTest_GetFullTimestampString();
        mpInstance->TimeUtilTest_GetSimpleTimestampString();

        mpInstance->TimeUtilTest_QueryPerformanceFrequency();
        mpInstance->TimeUtilTest_QueryPerformanceCounter();
        mpInstance->TimeUtilTest_TimeDiff();
    }

    void TimeUtilTest::TimeUtilTest_GetDateString()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_GetDateString -----------------------------------" << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "Current Date String: %s",
                       Shuanglong::Utils::TimeUtil::GetDateString().c_str());
    }

    void TimeUtilTest::TimeUtilTest_GetTimeString()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_GetTimeString -----------------------------------" << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "Current Time String: %s",
                       Shuanglong::Utils::TimeUtil::GetTimeString().c_str());
    }

    void TimeUtilTest::TimeUtilTest_GetDateTimeString()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_GetDateTimeString -----------------------------------" << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "Current DateTime String: %s",
                       Shuanglong::Utils::TimeUtil::GetDateTimeString().c_str());
    }

    void TimeUtilTest::TimeUtilTest_GetFormatTimeString()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_GetFormatTimeString -----------------------------------" << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "Current Date String: %s",
                       Shuanglong::Utils::TimeUtil::GetFormatTimeString("%Y-%m-%d").c_str());
        mpLog->Console(SL_CODE_LOCATION, "Current Time String: %s",
                       Shuanglong::Utils::TimeUtil::GetFormatTimeString("%H:%M:%S").c_str());
        mpLog->Console(SL_CODE_LOCATION, "Current DateTime String: %s",
                       Shuanglong::Utils::TimeUtil::GetFormatTimeString("%Y-%m-%d %H:%M:%S").c_str());
    }

    void TimeUtilTest::TimeUtilTest_GetCurrentTimestamp()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_GetCurrentTimestamp -----------------------------------" << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "Current Timestamp: %llu", Shuanglong::Utils::TimeUtil::GetCurrentTimestamp());
    }

    void TimeUtilTest::TimeUtilTest_GetFullTimestampString()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_GetFullTimestampString -----------------------------------" << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "Current Full Timestamp String: %s",
                       Shuanglong::Utils::TimeUtil::GetFullTimestampString().c_str());
    }

    void TimeUtilTest::TimeUtilTest_GetSimpleTimestampString()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_GetSimpleTimestampString -----------------------------------" << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "Current Simple Timestamp String: %s",
                       Shuanglong::Utils::TimeUtil::GetSimpleTimestampString().c_str());
    }

    void TimeUtilTest::TimeUtilTest_QueryPerformanceFrequency()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_QueryPerformanceFrequency -----------------------------------" << std::endl;
        long long frequency = Shuanglong::Utils::TimeUtil::QueryPerformanceFrequency();
        std::cout << "frequency: " << frequency << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "TimeUtil::QueryPerformanceFrequency PerformanceFrequency: %llu", frequency);
    }

    void TimeUtilTest::TimeUtilTest_QueryPerformanceCounter()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_QueryPerformanceCounter -----------------------------------" << std::endl;
        long long curWinTime = Shuanglong::Utils::TimeUtil::QueryPerformanceCounter();
        std::cout << "curWinTime: " << curWinTime << std::endl;
        mpLog->Console(SL_CODE_LOCATION, "TimeUtil::QueryPerformanceCounter PerformanceCounter: %llu", curWinTime);
    }

    void TimeUtilTest::TimeUtilTest_TimeDiff()
    {
        std::cout << std::endl
            << "----------------------------------- TimeUtilTest_TimeDiff -----------------------------------" << std::endl;

        time_t timeTest;
        tm tmStruct;
        time(&timeTest);
        gmtime_s(&tmStruct, &timeTest);
        mpLog->Console(SL_CODE_LOCATION, "gmtimes %04d-%02d-%02d %02d:%02d:%02d",
                       tmStruct.tm_year + 1900, tmStruct.tm_mon + 1, tmStruct.tm_mday, tmStruct.tm_hour, tmStruct.tm_min, tmStruct.tm_sec);
        timeTest += 28800;
        gmtime_s(&tmStruct, &timeTest);
        mpLog->Console(SL_CODE_LOCATION, "locatTimes=gmtimes+28800 %04d-%02d-%02d %02d:%02d:%02d",
                       tmStruct.tm_year + 1900, tmStruct.tm_mon + 1, tmStruct.tm_mday, tmStruct.tm_hour, tmStruct.tm_min, tmStruct.tm_sec);

        tm gmTime;
        tm loTime;
        gmtime_s(&gmTime, &timeTest);
        time_t gmt = mktime(&gmTime);
        localtime_s(&loTime, &timeTest);
        time_t lot = mktime(&loTime);
        double diff = difftime(lot, gmt);
        mpLog->Console(SL_CODE_LOCATION, "DIFF (From Greenwich to Local) = %lf", diff);

        _tzset();// set time environment variables: assign values to three global variables:_daylignt,_timezone and _tzname

        // --> About Time Zone
        int dayLightHours;
        _get_daylight(&dayLightHours);// daylight saving time offset in hours

        long dayLightSeconds;
        _get_dstbias(&dayLightSeconds);// daylight saving time offset in seconds

        long timeZone;
        int errorCode = _get_timezone(&timeZone);

        char timeZoneName[64];
        size_t nameLen;
        _get_tzname(&nameLen, timeZoneName, sizeof(timeZoneName), 0);

        mpLog->Console(SL_CODE_LOCATION, "dayLightHours=%d dayLightSeconds=%ld timeZone=%ld[%d] zoneName=%s errorCode=%d",
                       dayLightHours, dayLightSeconds, timeZone, nameLen, timeZoneName, errorCode);

        // --> Structure specifies information specific to the time zone.
        SYSTEMTIME localSysTime;
        GetLocalTime(&localSysTime);
        SYSTEMTIME gmtSysTime;
        GetSystemTime(&gmtSysTime);
        TIME_ZONE_INFORMATION timeZoneInfo;
        GetTimeZoneInformation(&timeZoneInfo);
        timeZoneInfo.StandardDate = gmtSysTime;
        timeZoneInfo.DaylightDate = localSysTime;
        mpLog->Console(SL_CODE_LOCATION, "\n"
                       "%16s %-30s = %ld\n"  // TIME_ZONE_INFORMATION.Bias
                       "%16s %-30s = %s\n"   // TIME_ZONE_INFORMATION.StandardName
                       "%16s %-30s = %ld\n"  // TIME_ZONE_INFORMATION.StandardBias
                       "%16s %-30s = %s\n"   // TIME_ZONE_INFORMATION.DaylightName
                       "%16s %-30s = %ld\n", // TIME_ZONE_INFORMATION.DaylightBias
                       "LONG", "Bias", timeZoneInfo.Bias,
                       "WCHAR", "StandardName", Utils::StringUtil::WStringToString(timeZoneInfo.StandardName).c_str(),
                       "LONG", "StandardBias", timeZoneInfo.StandardBias,
                       "WCHAR", "DaylightName", Utils::StringUtil::WStringToString(timeZoneInfo.DaylightName).c_str(),
                       "LONG", "DaylightBias", timeZoneInfo.DaylightBias);
        mpLog->Console(SL_CODE_LOCATION, "\n"
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.StandardDate.wYear
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.StandardDate.wMonth
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.StandardDate.wDayOfWeek
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.StandardDate.wDay
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.StandardDate.wHour
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.StandardDate.wMinute
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.StandardDate.wSecond
                       "%16s %-30s = %d\n", // TIME_ZONE_INFORMATION.StandardDate.wMilliseconds
                       "WORD", "StandardDate.wYear", timeZoneInfo.StandardDate.wYear,
                       "WORD", "StandardDate.wMonth", timeZoneInfo.StandardDate.wMonth,
                       "WORD", "StandardDate.wDayOfWeek", timeZoneInfo.StandardDate.wDayOfWeek,
                       "WORD", "StandardDate.wDay", timeZoneInfo.StandardDate.wDay,
                       "WORD", "StandardDate.wHour", timeZoneInfo.StandardDate.wHour,
                       "WORD", "StandardDate.wMinute", timeZoneInfo.StandardDate.wMinute,
                       "WORD", "StandardDate.wSecond", timeZoneInfo.StandardDate.wSecond,
                       "WORD", "StandardDate.wMilliseconds", timeZoneInfo.StandardDate.wMilliseconds);
        mpLog->Console(SL_CODE_LOCATION, "\n"
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.DaylightDate.wYear
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.DaylightDate.wMonth
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.DaylightDate.wDayOfWeek
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.DaylightDate.wDay
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.DaylightDate.wHour
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.DaylightDate.wMinute
                       "%16s %-30s = %d\n"  // TIME_ZONE_INFORMATION.DaylightDate.wSecond
                       "%16s %-30s = %d\n", // TIME_ZONE_INFORMATION.DaylightDate.wMilliseconds
                       "WORD", "DaylightDate.wYear", timeZoneInfo.DaylightDate.wYear,
                       "WORD", "DaylightDate.wMonth", timeZoneInfo.DaylightDate.wMonth,
                       "WORD", "DaylightDate.wDayOfWeek", timeZoneInfo.DaylightDate.wDayOfWeek,
                       "WORD", "DaylightDate.wDay", timeZoneInfo.DaylightDate.wDay,
                       "WORD", "DaylightDate.wHour", timeZoneInfo.DaylightDate.wHour,
                       "WORD", "DaylightDate.wMinute", timeZoneInfo.DaylightDate.wMinute,
                       "WORD", "DaylightDate.wSecond", timeZoneInfo.DaylightDate.wSecond,
                       "WORD", "DaylightDate.wMilliseconds", timeZoneInfo.DaylightDate.wMilliseconds);

        // timing precision test
        long long frequency = Shuanglong::Utils::TimeUtil::QueryPerformanceFrequency();
        DWORD tickCount = GetTickCount();
        clock_t clock = ::clock();
        LONGLONG counter = Shuanglong::Utils::TimeUtil::QueryPerformanceCounter();
        Sleep(3000);
        DWORD tickCount2 = GetTickCount();
        clock_t clock2 = ::clock();
        LONGLONG counter2 = Shuanglong::Utils::TimeUtil::QueryPerformanceCounter();
        mpLog->Console("tickCount = %lu     clock = %ld     counter = %llu",
                       tickCount2 - tickCount, clock2 - clock, (counter2 - counter) * 1000 / frequency);
    }
}
