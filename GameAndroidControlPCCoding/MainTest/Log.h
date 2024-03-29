#pragma once
#include "ILog.h"

#include <iostream>
#include <fstream>
#include <mutex>

#include <Utils/StringUtil.h>
#include <Utils/TimeUtil.h>

#define SL_DEBUG_ENABLE true
#define SL_DEFAULT_LOGFILE "E:\\TempLog.txt"

namespace Shuanglong
{
    class Log sealed : public ILog
    {
    private:
        Log();
        //static volatile bool      m_bInitFlag;
        //static std::mutex         m_mutex;
        static Log               *m_pInstance;
        static std::once_flag     m_instanceFlag;
        std::ofstream             m_osFile;

    public:
        ~Log();

        static Log* GetInstance();
        static void ClearInstance();

        virtual void Console(const char* msgFormat, ...);
        virtual void Console(CodeLocation location, const char* msgFormat, ...);
        virtual void WriteFile(const char* msgFormat, ...);
        virtual void WriteFile(CodeLocation location, const char* msgFormat, ...);

    private:
        static void init();
        void AddTimestamp(std::string& msgString);
        void AddCodeLocation(std::string& msgString, CodeLocation& location);

    private:
        class Helpper
        {
        public:
            Helpper()
            {}
            ~Helpper()
            {
                if (m_pInstance != nullptr)
                {
                    delete m_pInstance;
                }
            }
        };
        static Helpper helpper;
    };
}
