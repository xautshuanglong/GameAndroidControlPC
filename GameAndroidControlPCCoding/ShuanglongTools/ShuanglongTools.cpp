// ShuanglongTools.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ShuanglongTools.h"

#include "MainWindow.h"

using namespace Shuanglong::UI;

int APIENTRY WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
    DuiLib::CPaintManagerUI::SetInstance(hInstance);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());

    HRESULT hr = ::CoInitialize(NULL);
    if (FAILED(hr))
    {
        return 0;
    }

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

    return 0;
}
