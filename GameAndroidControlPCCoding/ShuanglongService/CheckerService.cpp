#include "stdafx.h"
#include "CheckerService.h"

#include "ThreadPool.h"

namespace Shuanglong::Service
{
    CheckerService::CheckerService(PTSTR serviceName, PTSTR pstrDisplayName, DWORD dwStartType, PTSTR pstrDependencies, PTSTR pstrAccount, PTSTR pstrPassword, BOOL canStop /* = TRUE */, BOOL canShutdown /* = TRUE */, BOOL canPauseContinue /* = FALSE */)
        : ServiceBase(serviceName, pstrDisplayName, dwStartType, pstrDependencies, pstrAccount, pstrPassword, canStop, canShutdown, canPauseContinue)
    {
    }

    CheckerService::~CheckerService()
    {
    }

    void CheckerService::OnStart(DWORD dwArgc, PTSTR *pstrArgv)
    {
    }

    void CheckerService::OnStop()
    {
    }

    void CheckerService::OnPause()
    {
    }

    void CheckerService::OnContinue()
    {
    }
}
