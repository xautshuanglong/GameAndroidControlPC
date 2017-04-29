#include "TimeUtilTest.h"

namespace ShuangLong
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
		std::cout << std::endl << "----------------------------------- TimeUtilTest_GetDateString -----------------------------------" << std::endl;
		mpLog->Console(SL_CODELOCATION, "Current Date String: %s", ShuangLong::Utils::TimeUtil::GetDateString().c_str());
	}

	void TimeUtilTest::TimeUtilTest_GetTimeString()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_GetTimeString -----------------------------------" << std::endl;
		mpLog->Console(SL_CODELOCATION, "Current Time String: %s", ShuangLong::Utils::TimeUtil::GetTimeString().c_str());
	}

	void TimeUtilTest::TimeUtilTest_GetDateTimeString()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_GetDateTimeString -----------------------------------" << std::endl;
		mpLog->Console(SL_CODELOCATION, "Current DateTime String: %s", ShuangLong::Utils::TimeUtil::GetDateTimeString().c_str());
	}

	void TimeUtilTest::TimeUtilTest_GetFormatTimeString()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_GetFormatTimeString -----------------------------------" << std::endl;
		mpLog->Console(SL_CODELOCATION, "Current Date String: %s", ShuangLong::Utils::TimeUtil::GetFormatTimeString("%Y-%m-%d").c_str());
		mpLog->Console(SL_CODELOCATION, "Current Time String: %s", ShuangLong::Utils::TimeUtil::GetFormatTimeString("%H:%M:%S").c_str());
		mpLog->Console(SL_CODELOCATION, "Current DateTime String: %s", ShuangLong::Utils::TimeUtil::GetFormatTimeString("%Y-%m-%d %H:%M:%S").c_str());
	}

	void TimeUtilTest::TimeUtilTest_GetCurrentTimestamp()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_GetCurrentTimestamp -----------------------------------" << std::endl;
		mpLog->Console(SL_CODELOCATION, "Current Timestamp: %llu", ShuangLong::Utils::TimeUtil::GetCurrentTimestamp());
	}

	void TimeUtilTest::TimeUtilTest_GetFullTimestampString()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_GetFullTimestampString -----------------------------------" << std::endl;
		mpLog->Console(SL_CODELOCATION, "Current Full Timestamp String: %s", ShuangLong::Utils::TimeUtil::GetFullTimestampString().c_str());
	}

	void TimeUtilTest::TimeUtilTest_GetSimpleTimestampString()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_GetSimpleTimestampString -----------------------------------" << std::endl;
		mpLog->Console(SL_CODELOCATION, "Current Simple Timestamp String: %s", ShuangLong::Utils::TimeUtil::GetSimpleTimestampString().c_str());
	}

	void TimeUtilTest::TimeUtilTest_QueryPerformanceFrequency()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_QueryPerformanceFrequency -----------------------------------" << std::endl;
		long long frequency = ShuangLong::Utils::TimeUtil::QueryPerformanceFrequency();
		std::cout << "frequency: " << frequency << std::endl;
		mpLog->Console(SL_CODELOCATION, "TimeUtil::QueryPerformanceFrequency PerformanceFrequency: %llu", frequency);
	}

	void TimeUtilTest::TimeUtilTest_QueryPerformanceCounter()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_QueryPerformanceCounter -----------------------------------" << std::endl;
		long long curWinTime = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
		std::cout << "curWinTime: " << curWinTime << std::endl;
		mpLog->Console(SL_CODELOCATION, "TimeUtil::QueryPerformanceCounter PerformanceCounter: %llu", curWinTime);
	}

	void TimeUtilTest::TimeUtilTest_TimeDiff()
	{
		std::cout << std::endl << "----------------------------------- TimeUtilTest_TimeDiff -----------------------------------" << std::endl;

		time_t timeTest;
		tm tmStruct;
		time(&timeTest);
		gmtime_s(&tmStruct, &timeTest);
		mpLog->Console(SL_CODELOCATION, "gmtimes %04d-%02d-%02d %02d:%02d:%02d", tmStruct.tm_year + 1900, tmStruct.tm_mon + 1, tmStruct.tm_mday, tmStruct.tm_hour, tmStruct.tm_min, tmStruct.tm_sec);
		timeTest += 28800;
		gmtime_s(&tmStruct, &timeTest);
		mpLog->Console(SL_CODELOCATION, "locatTimes=gmtimes+28800 %04d-%02d-%02d %02d:%02d:%02d", tmStruct.tm_year + 1900, tmStruct.tm_mon + 1, tmStruct.tm_mday, tmStruct.tm_hour, tmStruct.tm_min, tmStruct.tm_sec);

		tm gmTime;
		tm loTime;
		gmtime_s(&gmTime, &timeTest);
		time_t gmt = mktime(&gmTime);
		localtime_s(&loTime, &timeTest);
		time_t lot = mktime(&loTime);
		double diff = difftime(lot, gmt);
		mpLog->Console(SL_CODELOCATION, "DIFF (From Greenwich to Local) = %lf", diff);

		_tzset();

		int dayLight;
		_get_daylight(&dayLight);

		long timeZone;
		int errorCode = _get_timezone(&timeZone);

		char timeZoneName[64];
		size_t t;
		_get_tzname(&t, timeZoneName, sizeof(timeZoneName), 0);

		mpLog->Console(SL_CODELOCATION, "dayLight=%d timeZone=%ld[%d] zoneName=%s", dayLight, timeZone, errorCode, timeZoneName);

		long long frequency = ShuangLong::Utils::TimeUtil::QueryPerformanceFrequency();
		DWORD tickCount = GetTickCount();
		clock_t clock = ::clock();
		LONGLONG counter = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
		Sleep(3000);
		DWORD tickCount2 = GetTickCount();
		clock_t clock2 = ::clock();
		LONGLONG counter2 = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
		mpLog->Console("tickCount = %lu     clock = %ld     counter = %llu", tickCount2 - tickCount, clock2 - clock, (counter2 - counter) * 1000 / frequency);
	}
}
