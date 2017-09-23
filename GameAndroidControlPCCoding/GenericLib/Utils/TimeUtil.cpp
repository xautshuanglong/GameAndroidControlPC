#include "stdafx.h"
#include "TimeUtil.h"

#include <bcrypt.h>

namespace Shuanglong::Utils
{
    SYSTEMTIME TimeUtil::m_systemTime = { 0 };
    tm TimeUtil::m_tmCurTime = { 0 };
    time_t TimeUtil::m_tCurTime = 0;

    TimeUtil::~TimeUtil()
    {
    }

    /************************************************************************\
    Description: time string like YYYY-mm-dd
    Arguments  :
    \************************************************************************/
    std::string TimeUtil::GetDateString()
    {
        char timeBuffer[64];
        GetMyCurrentTime();
        strftime(timeBuffer, 64, "%Y-%m-%d", &m_tmCurTime);
        return std::string(timeBuffer);
    }

    /************************************************************************\
    Description: time string like HH:MM:SS
    Arguments  :
    \************************************************************************/
    std::string TimeUtil::GetTimeString()
    {
        char timeBuffer[64];
        GetMyCurrentTime();
        strftime(timeBuffer, 64, "%H:%M:%S", &m_tmCurTime);
        return std::string(timeBuffer);
    }

    /************************************************************************\
        Description: time string like YYYY-mm-dd HH:MM:SS
        Arguments  :
    \************************************************************************/
    std::string TimeUtil::GetDateTimeString()
    {
        char timeBuffer[64];
        GetMyCurrentTime();
        strftime(timeBuffer, 64, "%Y-%m-%d %H:%M:%S", &m_tmCurTime);
        return std::string(timeBuffer);
    }

    /************************************************************************\
        Description: time string formated by specified pattern string
        Arguments  :
        const char* timeFormat
            pattern string combined with charactor supplied at
            the begin of header file.
    \************************************************************************/
    std::string TimeUtil::GetFormatTimeString(const char* timeFormat)
    {
        char timeBuffer[128];
        GetMyCurrentTime();
        strftime(timeBuffer, 128, timeFormat, &m_tmCurTime);
        return std::string(timeBuffer);
    }

    /************************************************************************\
        Description: retrieve timestamp int64
        Arguments  :
    \************************************************************************/
    INT64 TimeUtil::GetCurrentTimestamp()
    {
        GetMyCurrentTime();
        return m_tCurTime;
    }

    /************************************************************************\
        Description: timestamp like YYYY-mm-dd HH:MM:SS.sss
        Arguments  :
    \************************************************************************/
    std::string TimeUtil::GetFullTimestampString()
    {
        ::GetLocalTime(&m_systemTime);
        char timeBuffer[64];
        sprintf_s(timeBuffer, "%4d-%02d-%02d %02d:%02d:%02d.%03d",
                  m_systemTime.wYear, m_systemTime.wMonth, m_systemTime.wDay,
                  m_systemTime.wHour, m_systemTime.wMinute, m_systemTime.wSecond, m_systemTime.wMilliseconds);
        return std::string(timeBuffer);
    }

    /************************************************************************\
        Description: timestamp like HH:MM:SS.sss
        Arguments  :
    \************************************************************************/
    std::string TimeUtil::GetSimpleTimestampString()
    {
        GetLocalTime(&m_systemTime);
        char timeBuffer[64];
        sprintf_s(timeBuffer, "%02d:%02d:%02d.%03d",
                  m_systemTime.wHour, m_systemTime.wMinute, m_systemTime.wSecond, m_systemTime.wMilliseconds);
        return std::string(timeBuffer);
    }

    LONGLONG TimeUtil::QueryPerformanceFrequency()
    {
        LARGE_INTEGER largeInt;
        ::QueryPerformanceFrequency(&largeInt);
        return largeInt.QuadPart;
    }

    LONGLONG TimeUtil::QueryPerformanceCounter()
    {
        LARGE_INTEGER largeInt;
        ::QueryPerformanceCounter(&largeInt);
        return largeInt.QuadPart;
    }


    void TimeUtil::IncreaseTimerPrecision()
    {
        typedef NTSTATUS(CALLBACK * NTSETTIMERRESOLUTION)(IN ULONG DesiredTime, IN BOOLEAN SetResolution, OUT PULONG ActualTime);
        typedef NTSTATUS(CALLBACK * NTQUERYTIMERRESOLUTION)(OUT PULONG MaximumTime, OUT PULONG MinimumTime, OUT PULONG CurrentTime);

        HINSTANCE hNtDll = ::LoadLibrary(L"NTDLL.dll");
        if (hNtDll != NULL)
        {
            ULONG MinimumResolution = 0;
            ULONG MaximumResolution = 0;
            ULONG ActualResolution = 0;

            NTQUERYTIMERRESOLUTION NtQueryTimerResolution = (NTQUERYTIMERRESOLUTION)GetProcAddress(hNtDll, "NtQueryTimerResolution");
            NTSETTIMERRESOLUTION NtSetTimerResolution = (NTSETTIMERRESOLUTION)GetProcAddress(hNtDll, "NtSetTimerResolution");

            if (NtQueryTimerResolution != NULL && NtSetTimerResolution != NULL)
            {
                NtQueryTimerResolution(&MinimumResolution, &MaximumResolution, &ActualResolution);
                if (MaximumResolution != 0)
                {
                    NtSetTimerResolution(MaximumResolution, TRUE, &ActualResolution);
                    NtQueryTimerResolution(&MinimumResolution, &MaximumResolution, &ActualResolution);
                }
            }
            ::FreeLibrary(hNtDll);
        }
    }

    void TimeUtil::GetMyCurrentTime()
    {
        ::time(&m_tCurTime);
        ::localtime_s(&m_tmCurTime, &m_tCurTime);

        //long timeZoneOffset;
        //time_t curTimeTest;
        //::time(&curTimeTest);
        //_tzset();
        //_get_timezone(&timeZoneOffset);
        //curTimeTest -= timeZoneOffset;
        //::gmtime_s(&m_tmCurTime, &curTimeTest);// 标准时间，需要根据时区自行调整
    }
}
