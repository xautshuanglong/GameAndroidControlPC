// ShuanglongTools.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ShuanglongTools.h"

#include <breakpad/exception_handler.h>
#include <Utils/LogUtil.h>

#include "LogManager.h"
#include "MainWindow.h"

using namespace Shuanglong::UI;
using namespace Shuanglong::Utils;
using namespace Shuanglong::Logger;
using namespace google_breakpad;

static ExceptionHandler* gpExecptinHandler = nullptr;

bool OnMinidumpGenerated(const wchar_t* dump_path,
                         const wchar_t* minidump_id,
                         void* context,
                         EXCEPTION_POINTERS* exinfo,
                         MDRawAssertionInfo* assertion,
                         bool succeeded);

int APIENTRY WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
    LogManager::Initialize();

    DuiLib::CPaintManagerUI::SetInstance(hInstance);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());

    HRESULT hr = ::CoInitialize(NULL);
    if (FAILED(hr))
    {
        return 0;
    }

    // This is needed for CRT to not show dialog for invalid param
    // failures and instead let the code handle it.
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_REPORT_MODE);
    gpExecptinHandler = new ExceptionHandler(L".\\", NULL,
                                             OnMinidumpGenerated, NULL,
                                             ExceptionHandler::HANDLER_ALL,
                                             MiniDumpNormal, L"", NULL);

    HRSRC findRes = ::FindResource(NULL, MAKEINTRESOURCE(IDR_XML_CONFIG), L"XML");
    if (findRes != NULL)
    {
        DWORD resSize = ::SizeofResource(NULL, findRes);
        HGLOBAL resGlobal = ::LoadResource(NULL, findRes);
        LPVOID pBuffer = ::LockResource(resGlobal);

        char xml[2560] = { 0 };
        memcpy_s(xml, 2560, pBuffer, resSize);
        OutputDebugStringA(xml);

        ::FreeResource(resGlobal);
    }

    MainWindow *pMainWin = new MainWindow();
    if (pMainWin != nullptr)
    {
        pMainWin->CreateDuiWindow(NULL, TEXT("ShuanglongTools"), UI_WNDSTYLE_FRAME&~WS_SYSMENU, WS_EX_STATICEDGE | WS_EX_APPWINDOW);
        pMainWin->SetIcon(IDI_HORSEWORD);
        pMainWin->CenterWindow();
        pMainWin->ShowWindow(true);
        DuiLib::CPaintManagerUI::MessageLoop();
        delete pMainWin;
        pMainWin = nullptr;
    }

    DuiLib::CPaintManagerUI::Term();
    MainWindow::CleanUp();

    ::CoUninitialize();
    LogManager::Uninitialize();

    return 0;
}

bool OnMinidumpGenerated(const wchar_t* dump_path,
                         const wchar_t* minidump_id,
                         void* context,
                         EXCEPTION_POINTERS* exinfo,
                         MDRawAssertionInfo* assertion,
                         bool succeeded)
{
    ::MessageBox(NULL, L"Crashed!", L"Error", MB_OK);

    return succeeded;
}
