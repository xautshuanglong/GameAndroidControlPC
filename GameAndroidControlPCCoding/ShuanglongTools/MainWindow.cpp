#include "stdafx.h"
#include "MainWindow.h"

namespace Shuanglong::UI
{
    const TCHAR* const kMainBtnCtrlClose = _T("closebtn");
    const TCHAR* const kMainBtnCtrlMin = _T("minbtn");
    const TCHAR* const kMainBtnCtrlMax = _T("maxbtn");
    const TCHAR* const kMainBtnCtrlRestore = _T("restorebtn");

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

    LRESULT MainWindow::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        CDuiString formatStr;
        formatStr.Format(TEXT("MainWindow::OnNcPaint uMsg=%u wParam=%u lParam=%u bHandled=%d\n"),
                         uMsg, wParam, lParam, bHandled);
        OutputDebugString(formatStr.GetData());
        //if (wParam == 1)
        //{
        //    HWND paintWnd = m_PaintManager.GetPaintWindow();
        //    PAINTSTRUCT ps = { 0 };
        //    ::BeginPaint(paintWnd, &ps);
        //    ::Rectangle(ps.hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom);
        //    ::EndPaint(paintWnd, &ps);
        //    bHandled = FALSE;
        //}

        bHandled = FALSE;
        return 0;
    }

    void MainWindow::OnPrepare(DuiLib::TNotifyUI& msg)
    {
    }

    void MainWindow::OnClick(DuiLib::TNotifyUI& msg)
    {
        WindowImplBase::OnClick(msg);
    }

    void MainWindow::OnTimer(DuiLib::TNotifyUI& msg)
    {
    }
}
