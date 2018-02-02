#pragma once

#include <string>

#define DEAFAULT_LOG_BUFFER_LENGTH 1024

#define DEAFAULT_LOG_FORMAT(buffer, fmt, length) \
va_list vaList;\
va_start(vaList, fmt);\
vsnprintf(buffer, DEAFAULT_LOG_BUFFER_LENGTH - 1, fmt, vaList);\
va_end(vaList);

#define CODE_LOCATION        Shuanglong::Logger::CodeLocation(__FUNCSIG__,__FILE__,__LINE__)
#define CODE_LOCATION_STRING Shuanglong::Logger::CodeLocation(__FUNCTION__,__FILE__,__LINE__).ToString().c_str()

namespace Shuanglong::Logger
{
    enum LogLevelType
    {
        LOG_LEVEL_DEBUG,
        LOG_LEVEL_INFO,
        LOG_LEVEL_WARN,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_FATAL,
        LOG_LEVEL_NONE
    };

    class CodeLocation;

    typedef void(*LoggerCallback)(const char *);
    typedef void(*LoggerCallbackExt)(LogLevelType level, CodeLocation *pLocation, std::string& msg);

    //************************************************************************\
    //    Author     : JiangChuanbiao
    //    Date       : 2017-1-9
    //    Description: 
    //************************************************************************/
    class Logger sealed
    {
    private:
        static LogLevelType                         mLevel;

    public:
        ~Logger();

        static void Console(char *fmt, ...);
        static void Console(CodeLocation location, char *fmt, ...);

        static void OutputDebug(char *fmt, ...);
        static void OutputDebug(CodeLocation location, char *fmt, ...);

        static void Init(LogLevelType level);
        static void InitLogCallback(LoggerCallback logCallback);
        static void InitLogCallback(LoggerCallbackExt logCallback);

        static void Debug(char *fmt, ...);
        static void Debug(CodeLocation location, char *fmt, ...);

        static void Info(char *fmt, ...);
        static void Info(CodeLocation location, char *fmt, ...);

        static void Warn(char *fmt, ...);
        static void Warn(CodeLocation location, char *fmt, ...);

        static void Error(char *fmt, ...);
        static void Error(CodeLocation location, char *fmt, ...);

        static void Fatal(char *fmt, ...);
        static void Fatal(CodeLocation location, char *fmt, ...);

        static std::string ConvertToString(std::wstring wstring);

    private:
        Logger();
        static std::string GetSystemTimeString();
        static std::string Logger::GetLevelString(LogLevelType logLevel);
        static void Log(LogLevelType level, std::string timestamp, std::string message);
        static void Log(LogLevelType level, std::string timestamp, CodeLocation location, std::string message);
        static LoggerCallback mpLogCallback;
        static LoggerCallbackExt mpLogCallbackExt;
    };

    class CodeLocation
    {
    public:
        CodeLocation();
        CodeLocation(char *funcname, char *fileName, int lineNumber);
        ~CodeLocation();

        std::string GetFunctionName();
        std::string GetFileName();
        std::string GetFullFileName();
        std::string ToString();
        int GetLineNumber();

    private:
        std::string m_strFileName, m_strShortFileName;
        std::string m_strFuncName;
        int m_lineNumber;

        void SubShortFileName();
    };
}

