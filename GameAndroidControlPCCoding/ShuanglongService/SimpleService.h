#pragma once

#include "ServiceBase.h"

namespace Shuanglong
{
    namespace Service
    {
        //************************************************************************\
        //    Author     : JiangChuanbiao
        //    Date       : 2018-4-19
        //    Description: ºÚµ• Windows Service ≤‚ ‘¿‡
        //************************************************************************/
        class SimpleService : public ServiceBase
        {
        public:
            SimpleService(PTSTR serviceName,
                          PTSTR pstrDisplayName,
                          DWORD dwStartType,
                          PTSTR pstrDependencies,
                          PTSTR pstrAccount,
                          PTSTR pstrPassword,
                          BOOL canStop = TRUE,
                          BOOL canShutdown = TRUE,
                          BOOL canPauseContinue = FALSE);
            ~SimpleService();

            virtual void OnStart(DWORD dwArgc, PTSTR *pstrArgv) override;
            virtual void OnStop() override;
            virtual void OnPause() override;
            virtual void OnContinue() override;

        private:
            BOOL m_fStopping;
            HANDLE m_hStoppedEvent;
        };
    }
}
