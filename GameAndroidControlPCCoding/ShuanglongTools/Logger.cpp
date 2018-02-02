#include "stdafx.h"
#include "Logger.h"

#include <windows.h>
#include <iostream>
#include <sstream>
#include <codecvt>

namespace Shuanglong::Logger
{
    LoggerCallback    Logger::mpLogCallback = nullptr;
    LoggerCallbackExt Logger::mpLogCallbackExt = nullptr;
    LogLevelType Logger::mLevel = LOG_LEVEL_NONE;

    Logger::Logger()
    {
        ;
    }

    Logger::~Logger()
    {
    }

    void Logger::Console(char *fmt, ...)
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

    void Logger::Console(CodeLocation location, char *fmt, ...)
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

    void Logger::OutputDebug(char *fmt, ...)
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

    void Logger::OutputDebug(CodeLocation location, char *fmt, ...)
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

    void Logger::Init(LogLevelType level)
    {
        mLevel = level;
    }

    void Logger::InitLogCallback(LoggerCallback logCallback)
    {
        mpLogCallback = logCallback;
    }

    void Logger::InitLogCallback(LoggerCallbackExt logCallback)
    {
        mpLogCallbackExt = logCallback;
    }

    void Logger::Debug(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_DEBUG)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_DEBUG, timestamp, msgBuffer);
        }
    }

    void Logger::Debug(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_DEBUG)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_DEBUG, timestamp, location, msgBuffer);
        }
    }

    void Logger::Warn(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_WARN)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_WARN, timestamp, msgBuffer);
        }
    }

    void Logger::Warn(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_WARN)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_WARN, timestamp, location, msgBuffer);
        }
    }

    void Logger::Info(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_INFO)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_INFO, timestamp, msgBuffer);
        }
    }

    void Logger::Info(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_INFO)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_INFO, timestamp, location, msgBuffer);
        }
    }

    void Logger::Error(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_ERROR)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_ERROR, timestamp, msgBuffer);
        }
    }

    void Logger::Error(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_ERROR)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_ERROR, timestamp, location, msgBuffer);
        }
    }

    void Logger::Fatal(char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_FATAL)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_FATAL, timestamp, msgBuffer);
        }
    }

    void Logger::Fatal(CodeLocation location, char *fmt, ...)
    {
        if (mLevel <= LOG_LEVEL_FATAL)
        {
            std::string timestamp = GetSystemTimeString();
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            DEAFAULT_LOG_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            Log(LOG_LEVEL_FATAL, timestamp, location, msgBuffer);
        }
    }

    void Logger::Log(LogLevelType level, std::string timestamp, std::string message)
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

    void Logger::Log(LogLevelType level, std::string timestamp, CodeLocation location, std::string message)
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

    std::string Logger::GetSystemTimeString()
    {
        SYSTEMTIME curTime;
        GetLocalTime(&curTime);
        char timeBuffer[100];
        sprintf_s(timeBuffer, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                  curTime.wYear, curTime.wMonth, curTime.wDay,
                  curTime.wHour, curTime.wMinute, curTime.wSecond, curTime.wMilliseconds);

        return std::string(timeBuffer);
    }

    std::string Logger::GetLevelString(LogLevelType logLevel)
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

    std::string Logger::ConvertToString(std::wstring wstring)
    {
        std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> cvtAnsi(new std::codecvt<wchar_t, char, std::mbstate_t>("chs"));
        std::string retString = cvtAnsi.to_bytes(wstring);

        return retString;
    }

    /*
    *  CodeLocation 实现部分
    */

    CodeLocation::CodeLocation()
    {
        m_lineNumber = 0;
        m_strFileName = "*";
        m_strFuncName = "*";
    }

    CodeLocation::CodeLocation(char *funcname, char *fileName, int lineNumber)
    {
        m_lineNumber = lineNumber;
        m_strFileName = fileName;
        m_strFuncName = funcname;

        size_t index = m_strFuncName.find_last_of('(');
        if (index != std::string::npos)
        {
            m_strFuncName.erase(index);
        }

        index = m_strFuncName.find_last_of(' ');
        if (index != std::string::npos)
        {
            m_strFuncName.erase(0, index + 1);
        }

        SubShortFileName();
    }

    CodeLocation::~CodeLocation()
    {}

    std::string CodeLocation::GetFunctionName()
    {
        std::string tempFuncName = "";
        size_t index = m_strFuncName.find_last_of("::");
        tempFuncName = m_strFuncName.substr(0, index - 1);
        index = tempFuncName.find_last_of("::");
        return m_strFuncName.substr(index + 1);
    }

    std::string CodeLocation::GetFileName()
    {
        return m_strShortFileName;
    }

    std::string CodeLocation::GetFullFileName()
    {
        return m_strFileName;
    }

    std::string CodeLocation::ToString()
    {
        std::string retString = "[  ]";
        std::string lineNumber;

        std::stringstream sstring;
        sstring << m_lineNumber;
        lineNumber = sstring.str();
        //sstring.clear();
        //sstring.str("");

        retString.insert(2, GetFunctionName() + " " + m_strShortFileName + ":" + lineNumber);

        return retString;
    }

    void CodeLocation::SubShortFileName()
    {
        size_t index = std::string::npos;
        m_strShortFileName = m_strFileName;

        index = m_strFileName.find_last_of('\\');
        if (index != std::string::npos)
        {
            m_strShortFileName.erase(0, index + 1);
        }
    }

    int CodeLocation::GetLineNumber()
    {
        return m_lineNumber;
    }
}
