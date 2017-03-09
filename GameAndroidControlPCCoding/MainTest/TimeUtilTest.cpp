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

		std::cout << std::endl << "----------------------------------- Time Utils Testing -----------------------------------" << std::endl;
		mpInstance->TimeUtilTest_QueryPerformanceFrequency();
		mpInstance->TimeUtilTest_QueryPerformanceCounter();
		mpInstance->TimeUtilTest_FormatTimestamp();
		mpInstance->TimeUtilTest_TimeDiff();
	}

	void TimeUtilTest::TimeUtilTest_QueryPerformanceFrequency()
	{
		long long frequency = ShuangLong::Utils::TimeUtil::QueryPerformanceFrequency();
		std::cout << "frequency: " << frequency << std::endl;
		mpLog->Console(SL_CODELOCATION, "Format test -- PerformanceCounter: %llu", frequency);
	}

	void TimeUtilTest::TimeUtilTest_QueryPerformanceCounter()
	{
		long long curWinTime = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
		std::cout << "curWinTime: " << curWinTime << std::endl;
		mpLog->Console(SL_CODELOCATION, "Format test -- PerformanceCounter: %llu", curWinTime);
	}

	void TimeUtilTest::TimeUtilTest_FormatTimestamp()
	{
		mpLog->Console(SL_CODELOCATION, "Current Full Time String: %s", ShuangLong::Utils::TimeUtil::GetFullTimeString().c_str());
	}

	void TimeUtilTest::TimeUtilTest_TimeDiff()
	{
		time_t timeTest;
		tm tmStruct;
		time(&timeTest);
		timeTest += 28800;
		gmtime_s(&tmStruct, &timeTest);
		mpLog->Console(SL_CODELOCATION, "gmtimes %04d-%02d-%02d %02d:%02d:%02d", tmStruct.tm_year + 1900, tmStruct.tm_mon + 1, tmStruct.tm_mday, tmStruct.tm_hour, tmStruct.tm_min, tmStruct.tm_sec);

		tm gmTime;
		tm loTime;
		gmtime_s(&gmTime, &timeTest);
		time_t gmt = mktime(&gmTime);
		localtime_s(&loTime, &timeTest);
		time_t lot = mktime(&loTime);
		double diff = difftime(gmt, lot);
		mpLog->Console(SL_CODELOCATION, "diff = %lf", diff);

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
