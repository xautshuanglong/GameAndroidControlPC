#include "stdafx.h"
#include "ProcessUtilTest.h"

#include <Psapi.h>
#include <TlHelp32.h>

namespace ShuangLong
{
    ProcessUtilTest* ProcessUtilTest::mpInstance = nullptr;

    ProcessUtilTest::ProcessUtilTest()
    {}

    ProcessUtilTest::~ProcessUtilTest()
    {}

    void ProcessUtilTest::Entry()
    {
        mpInstance = new ProcessUtilTest();
        mpInstance->mpLog = Log::GetInstance();

        std::cout << std::endl << "----------------------------------- Process Utils Testing -----------------------------------" << std::endl;
        //mpInstance->ProcessUtilTest_EnumProcess();
        mpInstance->ProcessUtilTest_CreateSnapshot();
        //mpInstance->ProcessUtilTest_GetPerformanceInfo();
        mpInstance->ProcessUtilTest_GetSystemInfo();
    }

    void ProcessUtilTest::ProcessUtilTest_EnumProcess()
    {
        DWORD errorCode = 0;
        HANDLE hProcess = INVALID_HANDLE_VALUE;
        TCHAR processName[512] = { 0 };
        HMODULE hModule = 0;
        DWORD processIDs[1024] = { 0 }, cbNeeded = 0;
        LONG cProcesses = 0;
        int succeesCount = 0, failedCount = 0;

        std::cout << std::endl << "----------------------------------- EnumProcesses -----------------------------------" << std::endl;
        if (EnumProcesses(processIDs, sizeof(processIDs), &cbNeeded))
        {
            cProcesses = cbNeeded / sizeof(DWORD);
            if (cProcesses > sizeof(processIDs))
            {
                cProcesses = sizeof(processIDs);
            }
            for (int i = 0; i < cProcesses; ++i)
            {
                if (processIDs[i] != 0)
                {
                    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIDs[i]);
                }
                if (hProcess != INVALID_HANDLE_VALUE)
                {
                    if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &cbNeeded))
                    {
                        GetModuleBaseName(hProcess, hModule, processName, sizeof(processName) / sizeof(TCHAR));
                        printf_s("%d-%d process name --> %s\n", i, processIDs[i], Utils::StringUtil::WStringToString(processName).c_str());
                        ++succeesCount;
                    }
                    else
                    {
                        errorCode = GetLastError();
                        printf_s("%d-%d EnumProcessModules failed errorCode=%d\n", i, processIDs[i], errorCode);
                        ++failedCount;
                    }
                }
                else
                {
                    printf_s("%d-%d process name --> %s\n", i, processIDs[i], "Error ---------------");
                }
            }
        }
        else
        {
            errorCode = GetLastError();
            printf_s("EnumProcesses failed errorCode=%d", errorCode);
        }

        printf_s("successCount=%d failedCount=%d cProcesses=%d\n", succeesCount, failedCount, cProcesses);
    }

    void ProcessUtilTest::ProcessUtilTest_CreateSnapshot()
    {
        int snapshotCount = 0;
        HANDLE hSnapshot = NULL;
        std::cout << std::endl << "----------------------------------- CreateToolhelp32Snapshot -----------------------------------" << std::endl;
        //hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);//创建快照  
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//创建快照  
        if (hSnapshot != INVALID_HANDLE_VALUE)
        {
            //枚举进程  
            PROCESSENTRY32  procEntry32;
            procEntry32.dwSize = sizeof(PROCESSENTRY32);

            if (Process32First(hSnapshot, &procEntry32))
            {
                do
                {
                    ++snapshotCount;
                    printf_s("%d process name --> %s\n", snapshotCount, Utils::StringUtil::WStringToString(procEntry32.szExeFile).c_str());
                } while (Process32Next(hSnapshot, &procEntry32));
            }

            CloseHandle(hSnapshot); //记得关掉handle 
        }

        printf_s("snapshotCount=%d\n", snapshotCount);
    }

    void ProcessUtilTest::ProcessUtilTest_GetPerformanceInfo()
    {
        std::cout << std::endl << "----------------------------------- Performance Testing -----------------------------------" << std::endl;
        DWORD errorCode = 0;
        PERFORMANCE_INFORMATION performanceInfo;
        BOOL res = FALSE;
        res = GetPerformanceInfo(&performanceInfo, sizeof(performanceInfo));
        if (res)
        {
            printf_s("%-45s = %lu\n", "PERFORMANCE_INFORMATION.cb", performanceInfo.cb);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.CommitTotal", performanceInfo.CommitTotal);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.CommitLimit", performanceInfo.CommitLimit);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.CommitPeak ", performanceInfo.CommitPeak);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.PhysicalTotal", performanceInfo.PhysicalTotal);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.PhysicalAvailable", performanceInfo.PhysicalAvailable);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.SystemCache", performanceInfo.SystemCache);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.PhysicalTotal ", performanceInfo.PhysicalTotal);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.KernelTotal", performanceInfo.KernelTotal);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.KernelPaged", performanceInfo.KernelPaged);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.KernelNonpaged", performanceInfo.KernelNonpaged);
            printf_s("%-45s = %llu\n", "PERFORMANCE_INFORMATION.PageSize ", performanceInfo.PageSize);
            printf_s("%-45s = %lu\n", "PERFORMANCE_INFORMATION.HandleCount", performanceInfo.HandleCount);
            printf_s("%-45s = %lu\n", "PERFORMANCE_INFORMATION.ProcessCount", performanceInfo.ProcessCount);
            printf_s("%-45s = %lu\n", "PERFORMANCE_INFORMATION.ThreadCount", performanceInfo.ThreadCount);
        }
        else
        {
            errorCode = GetLastError();
            printf_s("GetPerformanceInfo failed errorCode=%lu\n", errorCode);
        }
    }

    void ProcessUtilTest::ProcessUtilTest_GetSystemInfo()
    {
        std::cout << std::endl << "----------------------------------- GetSystemInfo Testing -----------------------------------" << std::endl;
        SYSTEM_INFO siSysInfo;
        GetSystemInfo(&siSysInfo);

        printf("Hardware information: \n");
        printf("  OEM ID: %u\n", siSysInfo.dwOemId);
        printf("  Number of processors: %u\n", siSysInfo.dwNumberOfProcessors);
        printf("  Page size: %u\n", siSysInfo.dwPageSize);
        printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
        printf("  Minimum application address: 0x%p\n", siSysInfo.lpMinimumApplicationAddress);
        printf("  Maximum application address: 0x%p\n", siSysInfo.lpMaximumApplicationAddress);
        printf("  Active processor mask: %llu\n", siSysInfo.dwActiveProcessorMask);
    }
}
