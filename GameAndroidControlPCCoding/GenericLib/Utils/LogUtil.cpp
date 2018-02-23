#include "LogUtil.h"

#include <windows.h>
#include <iostream>
#include <sstream>
#include <codecvt>

namespace Shuanglong::Utils
{
    LogUtilCallback    LogUtil::mpLogCallback = nullptr;
    LogUtilCallbackExt LogUtil::mpLogCallbackExt = nullptr;
    LogLevelType LogUtil::mLevel = LOG_LEVEL_NONE;

    LogUtil::LogUtil()
    {
        ;
    }

    LogUtil::~LogUtil()
    {
    }

    void LogUtil::Console(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_DEBUG)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string strMsg = GetSystemTimeString();
            strMsg.append(" ").append(msgBuffer);
            std::cout << strMsg << std::endl;
        }
    }

    void LogUtil::Console(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_DEBUG)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string strMessage = GetSystemTimeString();
            strMessage.append(" ").append(msgBuffer).append(" ").append(location.ToString());
            std::cout << strMessage << std::endl;
        }
    }

    void LogUtil::OutputDebug(char *fmt, ...)
    {
        if (mLevel > LOG_LEVEL_DEBUG)
        {
            return;
        }

        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);

        std::string strMsg = GetSystemTimeString();
        strMsg.append(" ").append(msgBuffer).append("\n");

        OutputDebugStringA(strMsg.c_str());
    }

    void LogUtil::OutputDebug(CodeLocation location, char *fmt, ...)
    {
        if (mLevel > LOG_LEVEL_DEBUG)
        {
            return;
        }

        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);

        std::string strMessage = GetSystemTimeString();
        strMessage.append(" ").append(msgBuffer).append(" ").append(location.ToString()).append("\n");

        OutputDebugStringA(strMessage.c_str());
    }

    void LogUtil::Init(LogLevelType level)
    {
        mLevel = level;
    }

    void LogUtil::InitLogCallback(LogUtilCallback logCallback)
    {
        mpLogCallback = logCallback;
    }

    void LogUtil::InitLogCallback(LogUtilCallbackExt logCallback)
    {
        mpLogCallbackExt = logCallback;
    }

    void LogUtil::Debug(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_DEBUG)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_DEBUG, timestamp, msgBuffer);
        }
    }

    void LogUtil::Debug(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_DEBUG)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_DEBUG, timestamp, location, msgBuffer);
        }
    }

    void LogUtil::Warn(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_WARN)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_WARN, timestamp, msgBuffer);
        }
    }

    void LogUtil::Warn(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_WARN)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_WARN, timestamp, location, msgBuffer);
        }
    }

    void LogUtil::Info(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_INFO)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_INFO, timestamp, msgBuffer);
        }
    }

    void LogUtil::Info(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_INFO)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_INFO, timestamp, location, msgBuffer);
        }
    }

    void LogUtil::Error(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_ERROR)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_ERROR, timestamp, msgBuffer);
        }
    }

    void LogUtil::Error(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_ERROR)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_ERROR, timestamp, location, msgBuffer);
        }
    }

    void LogUtil::Fatal(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_FATAL)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_FATAL, timestamp, msgBuffer);
        }
    }

    void LogUtil::Fatal(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_FATAL)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_FATAL, timestamp, location, msgBuffer);
        }
    }

    void LogUtil::Log(LogLevelType level, std::string timestamp, std::string message)
    {
        if (mpLogCallback != nullptr)
        {
            std::string strMessage = timestamp;
            std::string levelStr = GetLevelString(level);

            strMessage.append(" [" + levelStr + "] ")
                .append(message);

            mpLogCallback(strMessage.c_str());
        }

        if (mpLogCallbackExt != nullptr)
        {
            mpLogCallbackExt(level, nullptr, message);
        }
    }

    void LogUtil::Log(LogLevelType level, std::string timestamp, CodeLocation location, std::string message)
    {
        if (mpLogCallback != nullptr)
        {
            std::string strMessage = timestamp;
            std::string levelStr = GetLevelString(level);

            strMessage.append(" [" + levelStr + "] ")
                .append(message + " ")
                .append(location.ToString());
            mpLogCallback(strMessage.c_str());
        }

        if (mpLogCallbackExt != nullptr)
        {
            mpLogCallbackExt(level, &location, message);
        }
    }

    std::string LogUtil::GetSystemTimeString()
    {
        SYSTEMTIME curTime;
        GetLocalTime(&curTime);
        char timeBuffer[100];
        sprintf_s(timeBuffer, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                  curTime.wYear, curTime.wMonth, curTime.wDay,
                  curTime.wHour, curTime.wMinute, curTime.wSecond, curTime.wMilliseconds);

        return std::string(timeBuffer);
    }

    std::string LogUtil::GetLevelString(LogLevelType logLevel)
    {
        std::string retValue = "UNKNOW";
        switch (logLevel)
        {
        case LOG_LEVEL_NONE:
            retValue = "NONE";
            break;
        case LOG_LEVEL_DEBUG:
            retValue = "DEBUG";
            break;
        case LOG_LEVEL_INFO:
            retValue = "INFO";
            break;
        case LOG_LEVEL_WARN:
            retValue = "WARN";
            break;
        case LOG_LEVEL_ERROR:
            retValue = "ERROR";
            break;
        default:
            break;
        }

        return retValue;
    }

    std::string LogUtil::ConvertToString(std::wstring wstring)
    {
        std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> cvtAnsi(new std::codecvt<wchar_t, char, std::mbstate_t>("chs"));
        std::string retString = cvtAnsi.to_bytes(wstring);

        return retString;
    }
}
