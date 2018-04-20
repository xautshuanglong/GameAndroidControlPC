#pragma once

namespace Shuanglong
{
    namespace Service
    {
        //************************************************************************\
        //    Author     : JiangChuanbiao
        //    Date       : 2018-4-19
        //    Description: Windows Service 基类，约定基本功能接口。
        //************************************************************************/
        class ServiceBase;
        typedef std::list<ServiceBase*> ServiceList;

        class ServiceBase
        {

        private:
            DWORD                      mServiceStartType;
            PTSTR                      mServiceName;
            PTSTR                      mServiceDisplayName;
            PTSTR                      mServiceDependencies;
            PTSTR                      mServiceAccount;
            PTSTR                      mServicePassword;
            SERVICE_STATUS             mServiceStatus;
            SERVICE_STATUS_HANDLE      mServiceStatusHandle;
            static ServiceList         mServices;

        public:
            ServiceBase(PTSTR serviceName,
                        PTSTR pstrDisplayName,
                        DWORD dwStartType,
                        PTSTR pstrDependencies,
                        PTSTR pstrAccount,
                        PTSTR pstrPassword,
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
            // Service 状态变化响应函数
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
            void WriteEventLogEntry(PTSTR pszMessage, WORD wType);
            void WriteErrorLogEntry(PTSTR pszFunction, DWORD dwError = GetLastError());

            static void  WINAPI ServiceMainEntry(DWORD dwArgc, PTSTR *pArgv);
            static DWORD WINAPI ServiceCtrlHandlerEx(DWORD  dwControl, DWORD  dwEventType, LPVOID lpEventData, LPVOID lpContext);
        };
    }
}
