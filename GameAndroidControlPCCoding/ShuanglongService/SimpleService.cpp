#include "stdafx.h"
#include "SimpleService.h"

#include "ThreadPool.h"

namespace Shuanglong::Service
{
    SimpleService::SimpleService(PCTSTR serviceName, PCTSTR pstrDisplayName, DWORD dwStartType, PCTSTR pstrDependencies, PCTSTR pstrAccount, PCTSTR pstrPassword, BOOL canStop /* = TRUE */, BOOL canShutdown /* = TRUE */, BOOL canPauseContinue /* = FALSE */)
        : ServiceBase(serviceName, pstrDisplayName, dwStartType, pstrDependencies, pstrAccount, pstrPassword, canStop, canShutdown, canPauseContinue)
    {
    }

    SimpleService::~SimpleService()
    {
    }

    void SimpleService::OnStart(DWORD dwArgc, PTSTR *pstrArgv)
    {
    }

    void SimpleService::OnStop()
    {
    }

    void SimpleService::OnPause()
    {
    }

    void SimpleService::OnContinue()
    {
    }
}
