#pragma once

namespace Shuanglong
{
    namespace Service
    {
        //************************************************************************\
        //    Author     : JiangChuanbiao
        //    Date       : 2018-4-19
        //    Description: Windows Service ���࣬Լ���������ܽӿڡ�
        //************************************************************************/
        class ServiceBase;
        typedef std::list<ServiceBase*> ServiceList;

        class ServiceBase
        {

        private:
            DWORD                      mServiceStartType;
            PCTSTR                     mServiceName;
            PCTSTR                     mServiceDisplayName;
            PCTSTR                     mServiceDependencies;
            PCTSTR                     mServiceAccount;
            PCTSTR                     mServicePassword;
            SERVICE_STATUS             mServiceStatus;
            SERVICE_STATUS_HANDLE      mServiceStatusHandle;
            static ServiceList         mServices;

        public:
            ServiceBase(PCTSTR serviceName,
                        PCTSTR pstrDisplayName,
                        DWORD dwStartType,
                        PCTSTR pstrDependencies,
                        PCTSTR pstrAccount,
                        PCTSTR pstrPassword,
                        BOOL canStop = TRUE,
                        BOOL canShutdown = TRUE,
                        BOOL canPauseContinue = FALSE);
            ~ServiceBase();

            static BOOL Run(ServiceList services);
            static void Install(ServiceBase *pService);
            static void Uninstall(ServiceBase *pService);
            static void Install(ServiceList services);
            static void Uninstall(ServiceList services);
            void  Stop();

        protected:
            // Service ״̬�仯��Ӧ����
            virtual void OnStart(DWORD dwArgc, PTSTR *pszArgv);
            virtual void OnStop();
            virtual void OnPause();
            virtual void OnContinue();
            virtual void OnShutdown();

        private:
            void Start(DWORD dwArgc, PTSTR *pszArgv);
            void Pause();
            void Continue();
            void Shutdown();

            void SetServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode = NO_ERROR, DWORD dwWaitHint = 0);
            void WriteEventLogEntry(PCTSTR pszMessage, WORD wType);
            void WriteErrorLogEntry(PCTSTR pszFunction, DWORD dwError = GetLastError());

            static void  WINAPI ServiceMainEntry(DWORD dwArgc, PTSTR *pArgv);
            static DWORD WINAPI ServiceCtrlHandlerEx(DWORD  dwControl, DWORD  dwEventType, LPVOID lpEventData, LPVOID lpContext);
        };
    }
}
