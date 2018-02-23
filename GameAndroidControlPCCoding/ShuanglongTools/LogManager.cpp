#include "stdafx.h"
#include "LogManager.h"

namespace Shuanglong::Logger
{
    LogManager::LogManager()
    {
    }

    LogManager::~LogManager()
    {
    }

    void LogManager::Initialize()
    {
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
    }

    void LogManager::Log4cppCallbackHandler(LogLevelType level, CodeLocation *pLocation, std::string& msg)
    {
    }
}
