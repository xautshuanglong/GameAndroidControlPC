#pragma once

#include <Utils/LogUtil.h>

namespace log4cpp
{
    class PatternLayout;
    class FileAppender;
}

namespace Shuanglong::Logger
{
    using namespace Shuanglong::Utils;
    //************************************************************************\
    //    Author     : JiangChuanbiao
    //    Date       : 2017-1-9
    //    Description: 
    //************************************************************************/
    class LogManager sealed
    {
    private:
        static log4cpp::PatternLayout* mpLayoutTempFile;
        static log4cpp::PatternLayout* mpLayoutRollingFile;
        static log4cpp::FileAppender*  mpAppenderTempFile;
        static log4cpp::FileAppender*  mpAppenderRollingFile;

    public:
        ~LogManager();

        static void Initialize();
        static void Uninitialize();

    private:
        LogManager();
        static void Log4cppCallbackHandler(LogLevelType level, CodeLocation *pLocation, std::string& msg);
    };
}
