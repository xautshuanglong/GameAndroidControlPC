#include "stdafx.h"
#include "MainWindow.h"

namespace Shuanglong::UI
{
    //const TCHAR* const kMainBtnCtrlClose = _T("closebtn");
    //const TCHAR* const kMainBtnCtrlMin = _T("minbtn");
    //const TCHAR* const kMainBtnCtrlMax = _T("maxbtn");
    //const TCHAR* const kMainBtnCtrlRestore = _T("restorebtn");



    using namespace DuiLib;

    MainWindow::MainWindow()
    {
    }

    MainWindow::~MainWindow()
    {
    }

    LPCTSTR MainWindow::GetWindowClassName() const
    {
        return TEXT("MainWindow");
    }

    DuiLib::CDuiString MainWindow::GetSkinFolder()
    {
        return TEXT("skin\\");
    }

    DuiLib::CDuiString MainWindow::GetSkinFile()
    {
        //return TEXT("MainWindow.xml");
        return TEXT("ShuanglongTools.xml");
    }

    void MainWindow::Notify(TNotifyUI& msg)
    {
        if (msg.sType == TEXT("selectchanged"))
        {
            CDuiString senderName = msg.pSender->GetName();
            CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("MainTabLayout")));
            if (senderName ==TEXT("MainPage"))
                pControl->SelectItem(0);
            else if (senderName == TEXT("TestPage"))
                pControl->SelectItem(1);
            else if (senderName == TEXT("SettingPage"))
                pControl->SelectItem(2);
        }
        else if (msg.sType == DUI_MSGTYPE_CLICK)
        {
            int i = 0;
        }

        WindowImplBase::Notify(msg);
    }

    void MainWindow::OnFinalMessage(HWND hWnd)
    {
        WindowImplBase::OnFinalMessage(hWnd);
        ::PostQuitMessage(0);
    }

    void MainWindow::InitWindow()
    {
    }

    LRESULT MainWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;
        return 0;
    }

    LRESULT MainWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;
        return 0;
    }

    LRESULT MainWindow::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return (wParam == 0) ? TRUE : FALSE;
    }

    //LRESULT MainWindow::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    //{
    //    return FALSE;
    //}

    //LRESULT MainWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    //{
    //    return HTNOWHERE;
    //}

    //LRESULT MainWindow::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    //{
    //    bHandled = FALSE;
    //    return 0;
    //}

    void MainWindow::OnPrepare(DuiLib::TNotifyUI& msg)
    {
    }

    void MainWindow::OnClick(DuiLib::TNotifyUI& msg)
    {
        static bool minBtn = true;
        if (minBtn)
        {
            minBtn = false;
            COptionUI* pControl = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("SettingPage")));
            pControl->Selected(true);
        }
        else
        {
            minBtn = true;
            COptionUI* pControl = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("MainPage")));
            pControl->Selected(true);
        }

        WindowImplBase::OnClick(msg);
    }

    void MainWindow::OnTimer(DuiLib::TNotifyUI& msg)
    {
    }
}
