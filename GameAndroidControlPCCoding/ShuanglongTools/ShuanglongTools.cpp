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

    MainWindow *pMainWin = new MainWindow();
    pMainWin->CreateDuiWindow(NULL, TEXT("ShuanglongTools"), UI_WNDSTYLE_FRAME&~WS_SYSMENU, WS_EX_STATICEDGE | WS_EX_APPWINDOW);
    pMainWin->SetIcon(IDI_HORSEWORD);
    pMainWin->CenterWindow();
    pMainWin->ShowWindow(true);

    DuiLib::CPaintManagerUI::MessageLoop();
    DuiLib::CPaintManagerUI::Term();

    ::CoUninitialize();

    return 0;
}

//class CFrameWindowWnd : public CWindowWnd, public INotifyUI
//{
//public:
//    CFrameWindowWnd() {};
//    LPCTSTR GetWindowClassName() const { return _T("UIMainFrame"); };
//    UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
//    void OnFinalMessage(HWND /*hWnd*/) { delete this; };
//
//    void Init() {}
//
//    bool OnHChanged(void* param)
//    {
//        TNotifyUI* pMsg = (TNotifyUI*)param;
//        if (pMsg->sType == _T("valuechanged"))
//        {
//            short H, S, L;
//            CPaintManagerUI::GetHSL(&H, &S, &L);
//            CPaintManagerUI::SetHSL(true, (static_cast<CSliderUI*>(pMsg->pSender))->GetValue(), S, L);
//        }
//        return true;
//    }
//
//    bool OnSChanged(void* param)
//    {
//        TNotifyUI* pMsg = (TNotifyUI*)param;
//        if (pMsg->sType == _T("valuechanged"))
//        {
//            short H, S, L;
//            CPaintManagerUI::GetHSL(&H, &S, &L);
//            CPaintManagerUI::SetHSL(true, H, (static_cast<CSliderUI*>(pMsg->pSender))->GetValue(), L);
//        }
//        return true;
//    }
//
//    bool OnLChanged(void* param)
//    {
//        TNotifyUI* pMsg = (TNotifyUI*)param;
//        if (pMsg->sType == _T("valuechanged"))
//        {
//            short H, S, L;
//            CPaintManagerUI::GetHSL(&H, &S, &L);
//            CPaintManagerUI::SetHSL(true, H, S, (static_cast<CSliderUI*>(pMsg->pSender))->GetValue());
//        }
//        return true;
//    }
//
//    bool OnAlphaChanged(void* param)
//    {
//        TNotifyUI* pMsg = (TNotifyUI*)param;
//        if (pMsg->sType == _T("valuechanged"))
//        {
//            m_pm.SetTransparent((static_cast<CSliderUI*>(pMsg->pSender))->GetValue());
//        }
//        return true;
//    }
//
//    void OnPrepare()
//    {
//        CSliderUI* pSilder = static_cast<CSliderUI*>(m_pm.FindControl(_T("alpha_controlor")));
//        if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnAlphaChanged);
//        pSilder = static_cast<CSliderUI*>(m_pm.FindControl(_T("h_controlor")));
//        if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnHChanged);
//        pSilder = static_cast<CSliderUI*>(m_pm.FindControl(_T("s_controlor")));
//        if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnSChanged);
//        pSilder = static_cast<CSliderUI*>(m_pm.FindControl(_T("l_controlor")));
//        if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnLChanged);
//    }
//
//    void Notify(TNotifyUI& msg)
//    {
//        if (msg.sType == _T("windowinit")) OnPrepare();
//        else if (msg.sType == _T("click"))
//        {
//            if (msg.pSender->GetName() == _T("insertimagebtn"))
//            {
//                CRichEditUI* pRich = static_cast<CRichEditUI*>(m_pm.FindControl(_T("testrichedit")));
//                if (pRich)
//                {
//                    pRich->RemoveAll();
//                }
//            }
//            else if (msg.pSender->GetName() == _T("changeskinbtn"))
//            {
//                if (CPaintManagerUI::GetResourcePath() == CPaintManagerUI::GetInstancePath())
//                    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
//                else
//                    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
//                CPaintManagerUI::ReloadSkin();
//            }
//        }
//    }
//
//    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
//    {
//        if (uMsg == WM_CREATE)
//        {
//            m_pm.Init(m_hWnd);
//            CDialogBuilder builder;
//            CControlUI* pRoot = builder.Create(_T("skin\\ShuanglongTools.xml"), (UINT)0, NULL, &m_pm);
//            ASSERT(pRoot && "Failed to parse XML");
//            m_pm.AttachDialog(pRoot);
//            m_pm.AddNotifier(this);
//            Init();
//            return 0;
//        }
//        else if (uMsg == WM_DESTROY)
//        {
//            ::PostQuitMessage(0L);
//        }
//        else if (uMsg == WM_ERASEBKGND)
//        {
//            return 1;
//        }
//        LRESULT lRes = 0;
//        if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
//        return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
//    }
//
//public:
//    CPaintManagerUI m_pm;
//};
//
//int APIENTRY WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
//{
//    CPaintManagerUI::SetInstance(hInstance);
//    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
//
//    HRESULT hr = ::CoInitialize(NULL);
//    if (FAILED(hr)) return 0;
//
//    CFrameWindowWnd* pFrame = new CFrameWindowWnd();
//    if (pFrame == NULL) return 0;
//    pFrame->Create(NULL, _T("这是一个最简单的测试用exe，修改test1.xml就可以看到效果"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
//    pFrame->CenterWindow();
//    pFrame->ShowWindow(true);
//    CPaintManagerUI::MessageLoop();
//
//    ::CoUninitialize();
//    return 0;
//}
