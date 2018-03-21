#include "stdafx.h"
#include "LogManager.h"

#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

#include <Utils/DirectoryUtil.h>

namespace Shuanglong::Logger
{
    log4cpp::PatternLayout* LogManager::mpLayoutTempFile = nullptr;
    log4cpp::PatternLayout* LogManager::mpLayoutRollingFile = nullptr;
    log4cpp::FileAppender*  LogManager::mpAppenderTempFile = nullptr;
    log4cpp::FileAppender*  LogManager::mpAppenderRollingFile = nullptr;

    LogManager::LogManager()
    {
    }

    LogManager::~LogManager()
    {
    }

    void LogManager::Initialize()
    {
        log4cpp::Category& root = log4cpp::Category::getRoot();
        std::string logDir = DirectoryUtil::GetModuleDirectoryString() + "\\logs";

        if (!DirectoryUtil::IsDirectoryExist(logDir))
        {
            DirectoryUtil::CreateDirectoryByPath(logDir);
        }

        if (mpLayoutTempFile == nullptr)
        {
            mpLayoutTempFile = new log4cpp::PatternLayout();
        }
        mpLayoutTempFile->setConversionPattern("%d{%Y-%m-%d %H:%M:%S.%l} [%-5p] [%t] %c %m%n");
        if (mpAppenderTempFile == nullptr)
        {
            mpAppenderTempFile = new log4cpp::FileAppender("fileAppender", logDir+"\\TempDebug.log", false);
        }
        mpAppenderTempFile->setLayout(mpLayoutTempFile);
        root.addAppender(mpAppenderTempFile);

        if (mpLayoutRollingFile == nullptr)
        {
            mpLayoutRollingFile = new log4cpp::PatternLayout();
        }
        mpLayoutRollingFile->setConversionPattern("%d{%Y-%m-%d %H:%M:%S.%l} [%-5p] [%t] %c %m%n");
        if (mpAppenderRollingFile == nullptr)
        {
            mpAppenderRollingFile = new log4cpp::RollingFileAppender("rollingAppender", logDir+"\\RollingFile.log", 1024 * 1024, 10);
        }
        mpAppenderRollingFile->setLayout(mpLayoutRollingFile);
        root.addAppender(mpAppenderRollingFile);

#if _DEBUG
        LogUtil::Init(LOG_LEVEL_DEBUG);
#else
        LogUtil::Init(LOG_LEVEL_INFO);
#endif
        LogUtil::InitLogCallback(Log4cppCallbackHandler);
    }

    void LogManager::Uninitialize()
    {
        LogUtil::Init(LOG_LEVEL_NONE);
        LogUtil::InitLogCallback((LogUtilCallbackExt)nullptr);
        log4cpp::Category::shutdown();

        // log4cpp::Category::shutdown() 内部会释放相关指针

        //if (mpLayoutTempFile != nullptr)
        //{
        //    delete mpLayoutTempFile;
        //    mpLayoutTempFile = nullptr;
        //}
        //if (mpAppenderTempFile != nullptr)
        //{
        //    delete mpAppenderTempFile;
        //    mpAppenderTempFile = nullptr;
        //}
        //if (mpLayoutRollingFile != nullptr)
        //{
        //    delete mpLayoutRollingFile;
        //    mpLayoutRollingFile = nullptr;
        //}
        //if (mpAppenderRollingFile != nullptr)
        //{
        //    delete mpAppenderRollingFile;
        //    mpAppenderRollingFile = nullptr;
        //}
    }

    void LogManager::Log4cppCallbackHandler(LogLevelType level, CodeLocation *pLocation, std::string& msg)
    {
        log4cpp::Category& root = log4cpp::Category::getRoot();
        switch (level)
        {
        case Shuanglong::Utils::LOG_LEVEL_DEBUG:
            root.debug("%s --> %s", msg.c_str(), pLocation == nullptr ? "" : pLocation->ToString().c_str());
            break;
        case Shuanglong::Utils::LOG_LEVEL_INFO:
            root.info("%s --> %s", msg.c_str(), pLocation == nullptr ? "" : pLocation->ToString().c_str());
            break;
        case Shuanglong::Utils::LOG_LEVEL_WARN:
            root.warn("%s --> %s", msg.c_str(), pLocation == nullptr ? "" : pLocation->ToString().c_str());
            break;
        case Shuanglong::Utils::LOG_LEVEL_ERROR:
            root.error("%s --> %s", msg.c_str(), pLocation == nullptr ? "" : pLocation->ToString().c_str());
            break;
        case Shuanglong::Utils::LOG_LEVEL_FATAL:
            root.fatal("%s --> %s", msg.c_str(), pLocation == nullptr ? "" : pLocation->ToString().c_str());
            break;
        case Shuanglong::Utils::LOG_LEVEL_NONE:
            break;
        default:
            break;
        }
    }
}
