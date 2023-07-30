#pragma once
#include "ServiceBase.h"

namespace Shuanglong
{
    namespace Service
    {
        class CheckerService : public ServiceBase
        {
        public:
            CheckerService(PCTSTR serviceName,
                          PCTSTR pstrDisplayName,
                          DWORD dwStartType,
                          PCTSTR pstrDependencies,
                          PCTSTR pstrAccount,
                          PCTSTR pstrPassword,
                          BOOL canStop = TRUE,
                          BOOL canShutdown = TRUE,
                          BOOL canPauseContinue = FALSE);
            ~CheckerService();

            virtual void OnStart(DWORD dwArgc, PTSTR *pstrArgv);
            virtual void OnStop();
            virtual void OnPause() override;
            virtual void OnContinue() override;

        private:
            BOOL m_fStopping;
            HANDLE m_hStoppedEvent;
        };
    }
}

