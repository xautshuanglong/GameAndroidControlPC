#include "stdafx.h"
#include "ServiceBase.h"

#include <strsafe.h>

namespace Shuanglong::Service
{
    ServiceList ServiceBase::mServices;

    ServiceBase::ServiceBase(PCTSTR serviceName, PCTSTR pstrDisplayName, DWORD dwStartType, PCTSTR pstrDependencies, PCTSTR pstrAccount, PCTSTR pstrPassword, BOOL canStop /* = TRUE */, BOOL canShutdown /* = TRUE */, BOOL canPauseContinue /* = FALSE */)
    {
        mServiceName = (serviceName == NULL) ? TEXT("TempServiceName") : serviceName;
        mServiceDisplayName = (pstrDisplayName == NULL) ? TEXT("TempServiceDisplayName") : pstrDisplayName;
        mServiceDependencies = pstrDependencies;
        mServiceAccount = pstrAccount;
        mServicePassword = pstrPassword;
        mServiceStartType = dwStartType;
        mServiceStatusHandle = NULL;
        mServiceStatus.dwServiceType = SERVICE_WIN32_SHARE_PROCESS;
        mServiceStatus.dwCurrentState = SERVICE_START_PENDING;

        DWORD dwControlsAccepted = 0;
        if (canStop)
        {
            dwControlsAccepted |= SERVICE_ACCEPT_STOP;
        }
        if (canShutdown)
        {
            dwControlsAccepted |= SERVICE_ACCEPT_SHUTDOWN;
        }
        if (canPauseContinue)
        {
            dwControlsAccepted |= SERVICE_ACCEPT_PAUSE_CONTINUE;
        }
        mServiceStatus.dwControlsAccepted = dwControlsAccepted;

        mServiceStatus.dwWin32ExitCode = NO_ERROR;
        mServiceStatus.dwServiceSpecificExitCode = 0;
        mServiceStatus.dwCheckPoint = 0;
        mServiceStatus.dwWaitHint = 0;
    }

    ServiceBase::~ServiceBase()
    {}

    BOOL ServiceBase::Run(ServiceList services)
    {
        BOOL retValue = FALSE;
        mServices = services;
        size_t serviceCount = services.size();
        LPSERVICE_TABLE_ENTRY pServiceTableEntries = new SERVICE_TABLE_ENTRY[serviceCount + 1];
        size_t index = 0;

        for (ServiceBase* pServiceItem : mServices)
        {
            pServiceTableEntries[index].lpServiceName = const_cast<LPWSTR>(pServiceItem->mServiceName);
            pServiceTableEntries[index].lpServiceProc = ServiceBase::ServiceMainEntry;
            ++index;
        }

        pServiceTableEntries[index].lpServiceName = NULL;
        pServiceTableEntries[index].lpServiceProc = NULL;

        retValue = StartServiceCtrlDispatcher(pServiceTableEntries);
        if (pServiceTableEntries != nullptr)
        {
            delete[]pServiceTableEntries;
        }

        return retValue;
    }

    void ServiceBase::Install(ServiceBase *pService)
    {
        wchar_t szPath[MAX_PATH];
        SC_HANDLE schSCManager = NULL;
        SC_HANDLE schService = NULL;

        if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)) == 0)
        {
            printf_s("GetModuleFileName failed w/err 0x%08lx\n", GetLastError());
            goto Cleanup;
        }
        schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE);
        if (schSCManager == NULL)
        {
            printf_s("OpenSCManager failed w/err 0x%08lx\n", GetLastError());
            goto Cleanup;
        }
        schService = CreateService(
            schSCManager,                    // SCManager database
            pService->mServiceName,          // Name of service
            pService->mServiceDisplayName,   // Name to display
            SERVICE_QUERY_STATUS,            // Desired access
            SERVICE_WIN32_SHARE_PROCESS,     // Service type
            pService->mServiceStartType,     // Service start type
            SERVICE_ERROR_NORMAL,            // Error control type
            szPath,                          // Service's binary
            NULL,                            // No load ordering group
            NULL,                            // No tag identifier
            pService->mServiceDependencies,  // Dependencies
            pService->mServiceAccount,       // Service running account
            pService->mServicePassword       // Password of the account
        );
        if (schService == NULL)
        {
            printf_s("CreateService failed w/err 0x%08lx\n", GetLastError());
            goto Cleanup;
        }
        wprintf(L"%s is installed.\n", pService->mServiceName);

    Cleanup:
        if (schSCManager)
        {
            CloseServiceHandle(schSCManager);
            schSCManager = NULL;
        }
        if (schService)
        {
            CloseServiceHandle(schService);
            schService = NULL;
        }
    }

    void ServiceBase::Uninstall(ServiceBase *pService)
    {
        SC_HANDLE schSCManager = NULL;
        SC_HANDLE schService = NULL;
        SERVICE_STATUS ssSvcStatus = {};

        schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
        if (schSCManager == NULL)
        {
            wprintf(L"OpenSCManager failed w/err 0x%08lx\n", GetLastError());
            goto Cleanup;
        }

        schService = OpenService(schSCManager, pService->mServiceName, SERVICE_STOP | SERVICE_QUERY_STATUS | DELETE);
        if (schService == NULL)
        {
            wprintf(L"OpenService failed w/err 0x%08lx\n", GetLastError());
            goto Cleanup;
        }

        if (ControlService(schService, SERVICE_CONTROL_STOP, &ssSvcStatus))
        {
            wprintf(L"Stopping %s.", pService->mServiceName);
            Sleep(1000);

            while (QueryServiceStatus(schService, &ssSvcStatus))
            {
                if (ssSvcStatus.dwCurrentState == SERVICE_STOP_PENDING)
                {
                    wprintf(L".");
                    Sleep(1000);
                }
                else
                {
                    break;
                }
            }

            if (ssSvcStatus.dwCurrentState == SERVICE_STOPPED)
            {
                wprintf(L"\n%s is stopped.\n", pService->mServiceName);
            }
            else
            {
                wprintf(L"\n%s failed to stop.\n", pService->mServiceName);
            }
        }

        if (!DeleteService(schService))
        {
            wprintf(L"DeleteService failed w/err 0x%08lx\n", GetLastError());
            goto Cleanup;
        }

        wprintf(L"%s is removed.\n", pService->mServiceName);

    Cleanup:
        if (schSCManager)
        {
            CloseServiceHandle(schSCManager);
            schSCManager = NULL;
        }
        if (schService)
        {
            CloseServiceHandle(schService);
            schService = NULL;
        }
    }

    void ServiceBase::Install(ServiceList services)
    {
        for (ServiceBase *pService : services)
        {
            Install(pService);
        }
    }

    void ServiceBase::Uninstall(ServiceList services)
    {
        for (ServiceBase *pService : services)
        {
            Uninstall(pService);
        }
    }

    void ServiceBase::OnStart(DWORD dwArgc, PTSTR *pszArgv)
    {}

    void ServiceBase::OnStop()
    {}

    void ServiceBase::OnPause()
    {}

    void ServiceBase::OnContinue()
    {}

    void ServiceBase::OnShutdown()
    {
    }

    void ServiceBase::SetServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode /* = NO_ERROR */, DWORD dwWaitHint /* = 0 */)
    {
        static DWORD dwCheckPoint = 1;
        mServiceStatus.dwCurrentState = dwCurrentState;
        mServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
        mServiceStatus.dwWaitHint = dwWaitHint;

        mServiceStatus.dwCheckPoint =
            ((dwCurrentState == SERVICE_RUNNING) ||
            (dwCurrentState == SERVICE_STOPPED)) ? 0 : dwCheckPoint++;

        ::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);
    }

    void ServiceBase::WriteEventLogEntry(PCTSTR pszMessage, WORD wType)
    {
        HANDLE hEventSource = NULL;
        LPCWSTR lpszStrings[2] = { NULL, NULL };

        hEventSource = RegisterEventSource(NULL, mServiceName);
        if (hEventSource)
        {
            lpszStrings[0] = mServiceName;
            lpszStrings[1] = pszMessage;

            ReportEvent(hEventSource,  // Event log handle
                        wType,         // Event type
                        0,             // Event category
                        0,             // Event identifier
                        NULL,          // No security identifier
                        2,             // Size of lpszStrings array
                        0,             // No binary data
                        lpszStrings,   // Array of strings
                        NULL           // No binary data
            );

            DeregisterEventSource(hEventSource);
        }
    }

    void ServiceBase::WriteErrorLogEntry(PCTSTR pszFunction, DWORD dwError /* = GetLastError() */)
    {
        wchar_t szMessage[260];
        StringCchPrintf(szMessage, ARRAYSIZE(szMessage), L"%s failed : 0x%08lx (%U)", pszFunction, dwError, dwError);
        WriteEventLogEntry(szMessage, EVENTLOG_ERROR_TYPE);
    }

    void ServiceBase::Start(DWORD dwArgc, PTSTR *pszArgv)
    {
        try
        {
            SetServiceStatus(SERVICE_START_PENDING);
            OnStart(dwArgc, pszArgv);
            SetServiceStatus(SERVICE_RUNNING);
        }
        catch (DWORD dwError)
        {
            WriteErrorLogEntry(L"Service Start", dwError);
            SetServiceStatus(SERVICE_STOPPED, dwError);
        }
        catch (...)
        {
            WriteEventLogEntry(L"Service failed to start.", EVENTLOG_ERROR_TYPE);
            SetServiceStatus(SERVICE_STOPPED);
        }
    }

    void ServiceBase::Stop()
    {
        DWORD dwOriginalState = mServiceStatus.dwCurrentState;
        try
        {
            SetServiceStatus(SERVICE_STOP_PENDING);
            OnStop();
            SetServiceStatus(SERVICE_STOPPED);
        }
        catch (DWORD dwError)
        {
            WriteErrorLogEntry(L"ServiceBase::Stop", dwError);
            SetServiceStatus(dwOriginalState);
        }
        catch (...)
        {
            WriteEventLogEntry(L"Service failed to stop.", EVENTLOG_ERROR_TYPE);
            SetServiceStatus(dwOriginalState);
        }
    }

    void ServiceBase::Pause()
    {
        try
        {
            SetServiceStatus(SERVICE_PAUSE_PENDING);
            OnPause();
            SetServiceStatus(SERVICE_PAUSED);
        }
        catch (DWORD dwError)
        {
            WriteErrorLogEntry(L"Service Pause", dwError);
            SetServiceStatus(SERVICE_RUNNING);
        }
        catch (...)
        {
            WriteEventLogEntry(L"Service failed to pause.", EVENTLOG_ERROR_TYPE);
            SetServiceStatus(SERVICE_RUNNING);
        }
    }

    void ServiceBase::Continue()
    {
        try
        {
            SetServiceStatus(SERVICE_CONTINUE_PENDING);
            OnContinue();
            SetServiceStatus(SERVICE_RUNNING);
        }
        catch (DWORD dwError)
        {
            WriteErrorLogEntry(L"Service Continue", dwError);
            SetServiceStatus(SERVICE_PAUSED);
        }
        catch (...)
        {
            WriteEventLogEntry(L"Service failed to resume.", EVENTLOG_ERROR_TYPE);
            SetServiceStatus(SERVICE_PAUSED);
        }
    }

    void ServiceBase::Shutdown()
    {
        try
        {
            OnShutdown();
            SetServiceStatus(SERVICE_STOPPED);
        }
        catch (DWORD dwError)
        {
            WriteErrorLogEntry(L"ServiceBase::Shutdown", dwError);
        }
        catch (...)
        {
            WriteEventLogEntry(L"Service failed to shut down.", EVENTLOG_ERROR_TYPE);
        }
    }

    void ServiceBase::ServiceMainEntry(DWORD dwArgc, PTSTR *pArgv)
    {
        static int count = 0;
        wchar_t message[128] = { 0 };

        ServiceBase *pService = nullptr;
        for (ServiceBase* pServiceItem : mServices)
        {
            if (_tcscmp(pServiceItem->mServiceName, pArgv[0]) == 0)
            {
                wsprintf(message, L"ServiceMainEntry->%s count=%d tid=%u", pServiceItem->mServiceName, ++count, ::GetCurrentThreadId());
                pServiceItem->WriteEventLogEntry(message, EVENTLOG_INFORMATION_TYPE);
                pService = pServiceItem;
                break;
            }
        }

        if (pService != nullptr)
        {
            SERVICE_STATUS_HANDLE serviceHandle = RegisterServiceCtrlHandlerEx(pService->mServiceName, ServiceCtrlHandlerEx, pService);
            if (serviceHandle != NULL)
            {
                pService->mServiceStatusHandle = serviceHandle;
                pService->Start(dwArgc, pArgv);
            }
        }
    }

    DWORD ServiceBase::ServiceCtrlHandlerEx(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData, LPVOID lpContext)
    {
        ServiceBase *pService = static_cast<ServiceBase*>(lpContext);
        switch (dwControl)
        {
        case SERVICE_CONTROL_STOP:
            pService->Stop();
            break;
        case SERVICE_CONTROL_PAUSE:
            pService->Pause();
            break;
        case SERVICE_CONTROL_CONTINUE:
            pService->Continue();
            break;
        case SERVICE_CONTROL_SHUTDOWN:
            pService->Shutdown();
            break;
        case SERVICE_CONTROL_INTERROGATE:
            break;
        default:
            break;
        }

        return NO_ERROR;
    }
}
