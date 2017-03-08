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
		void static Entry();

		void TimeUtilTestAll();
	};
}
