#pragma once

#include "../GenericDefines.h"

#include <string>
#include "CodeLocation.h"

#define DEAFAULT_LOG_BUFFER_LENGTH 1024

#define DEAFAULT_LOG_FORMAT(buffer, fmt, length) \
va_list vaList;\
va_start(vaList, fmt);\
vsnprintf(buffer, DEAFAULT_LOG_BUFFER_LENGTH - 1, fmt, vaList);\
va_end(vaList);

namespace Shuanglong
{
    namespace Utils
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

        typedef void(*LogUtilCallback)(const char *);
        typedef void(*LogUtilCallbackExt)(LogLevelType level, CodeLocation *pLocation, std::string& msg);

        //************************************************************************\
        //    Author     : JiangChuanbiao
        //    Date       : 2017-1-9
        //    Description: 
        //************************************************************************/
        class GENERIC_EXPORT LogUtil
        {
        private:
            LogUtil();
            static LogLevelType         mLevel;
            static LogUtilCallback       mpLogCallback;
            static LogUtilCallbackExt    mpLogCallbackExt;

        public:
            ~LogUtil();
            static void Console(const char *fmt, ...);
            static void Console(CodeLocation location, const char *fmt, ...);

            static void OutputDebug(char *fmt, ...);
            static void OutputDebug(CodeLocation location, const char *fmt, ...);

            static void Init(LogLevelType level);
            static void InitLogCallback(LogUtilCallback logCallback);
            static void InitLogCallback(LogUtilCallbackExt logCallback);

            static void Debug(const char *fmt, ...);
            static void Debug(CodeLocation location, const char *fmt, ...);

            static void Info(const char *fmt, ...);
            static void Info(CodeLocation location, const char *fmt, ...);

            static void Warn(const char *fmt, ...);
            static void Warn(CodeLocation location, const char *fmt, ...);

            static void Error(const char *fmt, ...);
            static void Error(CodeLocation location, const char *fmt, ...);

            static void Fatal(const char *fmt, ...);
            static void Fatal(CodeLocation location, const char *fmt, ...);

            static std::string ConvertToString(std::wstring wstring);
        private:
            static std::string GetSystemTimeString();
            static std::string GetLevelString(LogLevelType logLevel);
            static void Log(LogLevelType level, std::string timestamp, std::string message);
            static void Log(LogLevelType level, std::string timestamp, CodeLocation location, std::string message);
        };
    }
}
