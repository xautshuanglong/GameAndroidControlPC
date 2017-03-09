#pragma once
#include "Log.h"

namespace ShuangLong
{
	class TimeUtilTest sealed
	{
	private:
		Log* mpLog = nullptr;

	public:
		TimeUtilTest();
		~TimeUtilTest();

		static TimeUtilTest *mpInstance;
		static void Entry();

		void TimeUtilTest_QueryPerformanceFrequency();
		void TimeUtilTest_QueryPerformanceCounter();
		void TimeUtilTest_FormatTimestamp();
		void TimeUtilTest_TimeDiff();
	};
}
