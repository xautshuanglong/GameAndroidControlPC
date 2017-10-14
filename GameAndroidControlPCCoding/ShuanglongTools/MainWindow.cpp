#include "stdafx.h"
#include "MainWindow.h"

namespace Shuanglong::UI
{
    const TCHAR* const kMainBtnCtrlClose = _T("closebtn");

    using namespace DuiLib;
    DUI_BEGIN_MESSAGE_MAP(MainWindow, WindowImplBase)
    //DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
    DUI_END_MESSAGE_MAP()

    MainWindow::MainWindow()
    {}

    MainWindow::~MainWindow()
    {
        ::PostQuitMessage(0);
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
        return TEXT("MainWindow.xml");
    }

    void MainWindow::OnFinalMessage(HWND hWnd)
    {
        WindowImplBase::OnFinalMessage(hWnd);
        delete this;
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

    void MainWindow::OnPrepare(DuiLib::TNotifyUI& msg)
    {
    }

    void MainWindow::OnClick(DuiLib::TNotifyUI& msg)
    {
        DuiLib::CDuiString sCtrlName = msg.pSender->GetName();
        if (sCtrlName == _T("closebtn"))
        {
            Close();
            return;
        }
        else if (sCtrlName == _T("minbtn"))
        {
            SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
            return;
        }
        else if (sCtrlName == _T("maxbtn"))
        {
            SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
            return;
        }
        else if (sCtrlName == _T("restorebtn"))
        {
            SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
            return;
        }
        return;
    }

    void MainWindow::OnTimer(DuiLib::TNotifyUI& msg)
    {
    }

    //void MainWindow::Notify(DuiLib::TNotifyUI& msg)
    //{
    //    if (_tcsicmp(msg.sType, DUI_MSGTYPE_WINDOWINIT) == 0)
    //    {
    //        OnPrepare(msg);
    //    }
    //    else if (_tcsicmp(msg.sType, DUI_MSGTYPE_KILLFOCUS) == 0)
    //    {
    //    }
    //    else if (_tcsicmp(msg.sType, DUI_MSGTYPE_CLICK) == 0)
    //    {
    //        DuiLib::CDuiString controlName = msg.pSender->GetName();
    //        if (controlName == kMainBtnCtrlClose)
    //        {
    //            OnExit(msg);
    //        }
    //    }
    //    else if (_tcsicmp(msg.sType, DUI_MSGTYPE_TIMER) == 0)
    //    {
    //        return OnTimer(msg);
    //    }
    //}

    void MainWindow::OnExit(DuiLib::TNotifyUI& mag)
    {
        Close();
    }
}
