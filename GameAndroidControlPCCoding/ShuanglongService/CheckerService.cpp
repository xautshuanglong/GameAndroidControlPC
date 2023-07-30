#include "stdafx.h"
#include "CheckerService.h"

#include "ThreadPool.h"

namespace Shuanglong::Service
{
    CheckerService::CheckerService(PCTSTR serviceName, PCTSTR pstrDisplayName, DWORD dwStartType, PCTSTR pstrDependencies, PCTSTR pstrAccount, PCTSTR pstrPassword, BOOL canStop /* = TRUE */, BOOL canShutdown /* = TRUE */, BOOL canPauseContinue /* = FALSE */)
        : ServiceBase(serviceName, pstrDisplayName, dwStartType, pstrDependencies, pstrAccount, pstrPassword, canStop, canShutdown, canPauseContinue)
        , m_fStopping(FALSE)
        , m_hStoppedEvent(INVALID_HANDLE_VALUE)
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
