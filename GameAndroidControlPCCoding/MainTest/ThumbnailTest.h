#pragma once

#include "Log.h"

namespace ShuangLong
{
    class ThumbnailTest sealed
    {
    private:
        ThumbnailTest();
        Log*                    mpLog;
        static ThumbnailTest   *mpInstance;

        HBITMAP                 mhBitmap;
        HWND                    mhWindow;
        HINSTANCE               mhInstance;

    public:
        ~ThumbnailTest();
        static void Entry();

    private:
        void IShellItemImageFactoryTest();
        void IThumbnailCacheTest();
        void InitWindow();
        void MessageLoop();
        static LRESULT CALLBACK MyDefWindowProcW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

        // Message handler
        static void OnPaintHandler(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        static void OnDestroyHandler(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
    };
}

