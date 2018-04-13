// ShuanglongService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <stdio.h>

// �����߳���ͣʱ�䣻
#define SLEEP_TIME 5000
// ��־�ļ�����·��
#define LOGFILE "E:\\memstatus.txt"

// ��ǰ����״̬
SERVICE_STATUS ServiceStatus;
// ������ƴ�����
SERVICE_STATUS_HANDLE ServiceStatusHandle;

int WriteToLog(char* str)
{
    FILE* log;
    fopen_s(&log, LOGFILE, "a+");
    if (log == NULL)
        return -1;
    fprintf(log, "%s\n", str);
    fclose(log);
    return 0;
}

int InitService()
{
    int result;
    result = WriteToLog("Monitoring started.");
    return(result);
}

void ServiceControlHandler(DWORD request)
{
    switch (request)
    {
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
        // ����ֹͣ
        WriteToLog("Monitoring stopped.");
        ServiceStatus.dwWin32ExitCode = 0;
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        break;
    default:
        break;
    }

    // �����������㱨����״̬
    SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

    return;
}

void ServiceMain(DWORD argc, LPWSTR argv)
{
    // ��ʼ���������͡� ״̬�� ���ܵĿ��Ʒ����Լ��ڴ��ķ���ֵ
    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;

    // ע�������ƴ�����
    ServiceStatusHandle = RegisterServiceCtrlHandler(
        L"MemoryStatus", // �������Ʊ����밲װ����ʱ������һ�£�
        (LPHANDLER_FUNCTION)ServiceControlHandler
    );
    if (ServiceStatusHandle == NULL)
    {
        // ����ע��ʧ��
        return;
    }
    // ��ʼ������
    int error = InitService();
    if (error)
    {
        // ��ʼ������ʧ�ܣ� ���÷���״̬Ϊ STOPPED ������
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        ServiceStatus.dwWin32ExitCode = -1;
        SetServiceStatus(ServiceStatusHandle, &ServiceStatus);
        return;
    }
    // ���ڷ����Ѿ��ɹ����������ˣ� �����������㱨״̬��
    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

    MEMORYSTATUS memory;
    // �����߳���ѭ���� ÿ�� 5 ���Ӷ�ȡϵͳ�ڴ�״̬�� �������־�ļ�
    while (ServiceStatus.dwCurrentState == SERVICE_RUNNING)
    {
        char buffer[16];
        GlobalMemoryStatus(&memory);
        sprintf_s(buffer, "%llu", memory.dwAvailPhys);
        int result = WriteToLog(buffer);
        if (result)
        {
            ServiceStatus.dwCurrentState = SERVICE_STOPPED;
            ServiceStatus.dwWin32ExitCode = -1;
            SetServiceStatus(ServiceStatusHandle, &ServiceStatus);
            return;
        }

        Sleep(SLEEP_TIME);
    }
    return;
}

int main()
{
    SERVICE_TABLE_ENTRY entryTables[] =
    {
        { L"MemoryStatus", (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        NULL
    };

    // Start the control dispatcher thread for our service
    StartServiceCtrlDispatcher(entryTables);
    return 0;
}
