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
        mpInstance->ProcessUtilTest_Try();
    }

    void ProcessUtilTest::ProcessUtilTest_Try()
    {
        DWORD errorCode = 0;
        DWORD processIDs[1024] = { 0 }, cbNeeded = 0, cProcesses = 0;
        HANDLE hProcess = INVALID_HANDLE_VALUE;
        HMODULE hModule = 0;
        TCHAR processName[512] = { 0 };

        int succeesCount = 0, failedCount = 0;
        int snapshotCount = 0;

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
                    printf_s("======================== %d --> pid=%d ===========================\n", i, processIDs[i]);
                }
            }
        }
        else
        {
            errorCode = GetLastError();
            printf_s("EnumProcesses failed errorCode=%d", errorCode);
        }

        HANDLE hSnapshot = NULL;
        std::cout << std::endl << "----------------------------------- CreateToolhelp32Snapshot -----------------------------------" << std::endl;
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);//创建快照  
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
                    printf_s("%d process name --> %s\n",snapshotCount , Utils::StringUtil::WStringToString(procEntry32.szExeFile).c_str());
                } while (Process32Next(hSnapshot, &procEntry32));
            }

            CloseHandle(hSnapshot); //记得关掉handle 
        }

        printf_s("snapshotCount=%d successCount=%d failedCount=%d cProcesses=%d\n", snapshotCount, succeesCount, failedCount, cProcesses);
    }
}
