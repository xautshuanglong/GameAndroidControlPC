// ShuanglongService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <stdio.h>

// 服务线程暂停时间；
#define SLEEP_TIME 5000
// 日志文件输入路径
#define LOGFILE "E:\\memstatus.txt"

// 当前服务状态
SERVICE_STATUS ServiceStatus;
// 服务控制处理函数
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
        // 服务停止
        WriteToLog("Monitoring stopped.");
        ServiceStatus.dwWin32ExitCode = 0;
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        break;
    default:
        break;
    }

    // 向服务管理器汇报服务状态
    SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

    return;
}

void ServiceMain(DWORD argc, LPWSTR argv)
{
    // 初始化服务类型、 状态、 接受的控制方法以及期待的返回值
    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;

    // 注册服务控制处理函数
    ServiceStatusHandle = RegisterServiceCtrlHandler(
        L"MemoryStatus", // 服务名称必须与安装服务时的名称一致；
        (LPHANDLER_FUNCTION)ServiceControlHandler
    );
    if (ServiceStatusHandle == NULL)
    {
        // 服务注册失败
        return;
    }
    // 初始化服务
    int error = InitService();
    if (error)
    {
        // 初始化服务失败， 设置服务状态为 STOPPED 并返回
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        ServiceStatus.dwWin32ExitCode = -1;
        SetServiceStatus(ServiceStatusHandle, &ServiceStatus);
        return;
    }
    // 现在服务已经成功运行起来了， 向服务管理器汇报状态。
    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

    MEMORYSTATUS memory;
    // 服务线程主循环， 每隔 5 秒钟读取系统内存状态， 输出到日志文件
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
