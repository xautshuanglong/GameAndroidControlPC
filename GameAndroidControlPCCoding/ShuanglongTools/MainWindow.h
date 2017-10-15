#pragma once

namespace Shuanglong
{
    namespace UI
    {
        using namespace DuiLib;
        class MainWindow : public DuiLib::WindowImplBase
        {
        private:
            DUI_DECLARE_MESSAGE_MAP()

        public:
            MainWindow();
            ~MainWindow();

            LPCTSTR GetWindowClassName() const;
            virtual DuiLib::CDuiString GetSkinFolder();
            virtual DuiLib::CDuiString GetSkinFile();
            virtual void OnFinalMessage(HWND hWnd);
            virtual void InitWindow();
            //virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
            virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
            virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

        protected:
            void OnPrepare(DuiLib::TNotifyUI& msg);
            void OnClick(DuiLib::TNotifyUI& msg);
            void OnTimer(DuiLib::TNotifyUI& msg);
            void OnExit(DuiLib::TNotifyUI& mag);
        };
    }
}
