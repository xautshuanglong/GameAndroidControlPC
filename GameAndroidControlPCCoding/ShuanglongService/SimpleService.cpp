#include "stdafx.h"
#include "SimpleService.h"

#include "ThreadPool.h"

namespace Shuanglong::Service
{
    SimpleService::SimpleService(PTSTR serviceName, PTSTR pstrDisplayName, DWORD dwStartType, PTSTR pstrDependencies, PTSTR pstrAccount, PTSTR pstrPassword, BOOL canStop /* = TRUE */, BOOL canShutdown /* = TRUE */, BOOL canPauseContinue /* = FALSE */)
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
