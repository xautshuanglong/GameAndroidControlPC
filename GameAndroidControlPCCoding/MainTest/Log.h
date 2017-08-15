#pragma once
#include "ILog.h"

#include <CodeLocation.h>
#include <StringUtil.h>
#include <TimeUtil.h>

#include <iostream>
#include <fstream>
#include <mutex>

#define SL_DEBUG_ENABLE true
#define SL_DEFAULT_LOGFILE "E:\\TempLog.txt"

namespace ShuangLong
{
    class Log sealed : public ILog
    {
    private:
        Log();
        //static volatile bool      m_bInitFlag;
        //static std::mutex         m_mutex;
        static Log               *m_mpInstance;
        static std::once_flag     m_instanceFlag;
        std::ofstream             m_osFile;

    public:
        ~Log();

        static Log* GetInstance();

        virtual void Console(const char* msgFormat, ...);
        virtual void Console(CodeLocation location, char* msgFormat, ...);
        virtual void WriteFile(const char* msgFormat, ...);
        virtual void WriteFile(CodeLocation location, char* msgFormat, ...);

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
                if (m_mpInstance != nullptr)
                {
                    delete m_mpInstance;
                }
            }
        };
        static Helpper helpper;
    };
}
