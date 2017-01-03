#include "stdafx.h"
#include "TimeUtil.h"

namespace ShuangLong
{
	namespace Utils
	{
		SYSTEMTIME TimeUtil::m_systemTime = { 0 };
		tm TimeUtil::m_tmCurTime = { 0 };
		time_t TimeUtil::m_tCurTime = 0;

		TimeUtil::TimeUtil()
		{
		}

		TimeUtil::~TimeUtil()
		{
		}

		std::string TimeUtil::GetFullTimeString()
		{
			char timeBuffer[64];
			GetCurrentTime();
			strftime(timeBuffer, 64, "%Y-%m-%d %H:%M:%S", &m_tmCurTime);
			return std::string(timeBuffer);
		}

		std::string TimeUtil::GetSimpleTimeString()
		{
			char timeBuffer[64];
			GetCurrentTime();
			strftime(timeBuffer, 64, "%H:%M:%S", &m_tmCurTime);
			return std::string(timeBuffer);
		}

		std::string TimeUtil::GetFormatTimeString(const char* timeFormat)
		{
			char timeBuffer[128];
			GetCurrentTime();
			strftime(timeBuffer, 128, timeFormat, &m_tmCurTime);
			return std::string(timeBuffer);
		}

		std::string TimeUtil::GetFullTimestamp()
		{
			::GetLocalTime(&m_systemTime);
			char timeBuffer[64];
			sprintf_s(timeBuffer, "%4d-%02d-%02d %02d:%02d:%02d.%03d",
				m_systemTime.wYear, m_systemTime.wMonth, m_systemTime.wDay,
				m_systemTime.wHour, m_systemTime.wMinute, m_systemTime.wSecond, m_systemTime.wMilliseconds);
			return std::string(timeBuffer);
		}

		std::string TimeUtil::GetSimpleTimestamp()
		{
			::GetLocalTime(&m_systemTime);
			char timeBuffer[64];
			sprintf_s(timeBuffer, "%02d:%02d:%02d.%03d",
				m_systemTime.wHour, m_systemTime.wMinute, m_systemTime.wSecond, m_systemTime.wMilliseconds);
			return std::string(timeBuffer);
		}

		void TimeUtil::GetCurrentTime()
		{
			time(&m_tCurTime);
			localtime_s(&m_tmCurTime, &m_tCurTime);
		}
	}
}
