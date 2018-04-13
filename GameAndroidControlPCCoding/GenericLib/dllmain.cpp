// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
)
{
    //std::cout << "Enter GenericLib DllMain tid=" << GetCurrentThreadId() << std::endl;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::cout << "case GenericLib DLL_PROCESS_ATTACH tid=" << GetCurrentThreadId() << std::endl;
        break;
    case DLL_THREAD_ATTACH:
        //std::cout << "case GenericLib DLL_THREAD_ATTACH tid=" << GetCurrentThreadId() << std::endl;
        break;
    case DLL_THREAD_DETACH:
        //std::cout << "case GenericLib DLL_THREAD_DETACH tid=" << GetCurrentThreadId() << std::endl;
        break;
    case DLL_PROCESS_DETACH:
        std::cout << "case GenericLib DLL_PROCESS_DETACH tid=" << GetCurrentThreadId() << std::endl;
        break;
    }
    //std::cout << "Leave GenericLib DllMain tid=" << GetCurrentThreadId() << std::endl;
    return TRUE;
}

