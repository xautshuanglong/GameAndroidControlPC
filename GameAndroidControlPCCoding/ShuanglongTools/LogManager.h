#pragma once

#include <Utils/LogUtil.h>

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
        LogManager();

    public:
        ~LogManager();

        static void Initialize();
        static void Uninitialize();

    private:
        static void Log4cppCallbackHandler(LogLevelType level, CodeLocation *pLocation, std::string& msg);
    };
}
