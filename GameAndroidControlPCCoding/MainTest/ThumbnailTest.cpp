#include "stdafx.h"
#include "ThumbnailTest.h"

#include <ShObjIdl.h>
#include <thumbcache.h>

namespace Shuanglong::Test
{
#define THUMBNAIL_SIZE 256

    ThumbnailTest* ThumbnailTest::mpInstance = nullptr;

    ThumbnailTest::ThumbnailTest():mhWindow(nullptr)
        , mhInstance(nullptr)
        , mhBitmap(nullptr)
    {}

    ThumbnailTest::~ThumbnailTest()
    {}

    void ThumbnailTest::Entry()
    {
        std::cout << "----------------------------- Thumbnail Testing -----------------------------" << std::endl;
        mpInstance = new ThumbnailTest();
        mpInstance->mpLog = Log::GetInstance();

        mpInstance->mhInstance = (HINSTANCE)GetModuleHandle(NULL);

#if 0
        mpInstance->IShellItemImageFactoryTest();
#else
        mpInstance->IThumbnailCacheTest();
#endif
    }

    void ThumbnailTest::IShellItemImageFactoryTest()
    {
        HRESULT                 res = S_FALSE;
        SIZE                    bitMapSize = { THUMBNAIL_SIZE,THUMBNAIL_SIZE };
        IShellItemImageFactory *pShImgFactory = nullptr;

        res = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(res))
        {
            res = SHCreateItemFromParsingName(TEXT("E:\\视频解码相关库\\F_5_Fly.mp4"), nullptr, IID_PPV_ARGS(&pShImgFactory));
            if (res == S_OK)
            {
                //mpLog->Console(SL_CODELOCATION, "SHCreateItemFromParsingName successfully.");
                res = pShImgFactory->GetImage(bitMapSize, SIIGBF_BIGGERSIZEOK, &mhBitmap);
                if (SUCCEEDED(res))
                {
                    InitWindow();
                }
                else
                {
                    mpLog->Console(SL_CODELOCATION, "GetImage failed errorCode=%lu", res);
                }
                pShImgFactory->Release();
            }
            else
            {
                mpLog->Console(SL_CODELOCATION, "SHCreateItemFromParsingName failed errorCode=%lu", res);
            }

            CoUninitialize();
        }
        else
        {
            mpLog->Console(SL_CODELOCATION, "CoInitializeEx failed errorCode=%lu", res);
        }

        MessageLoop();
    }

    void ThumbnailTest::IThumbnailCacheTest()
    {
        HRESULT res = S_FALSE;
        IShellItem *pShellItem = nullptr;
        IThumbnailProvider *pThumbProvider = nullptr;
        WTS_ALPHATYPE wtsAlpha;

        res = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(res))
        { 
            res = SHCreateItemFromParsingName(TEXT("E:\\视频解码相关库\\恐怖11：57.mp4"), nullptr, IID_PPV_ARGS(&pShellItem));
            if (SUCCEEDED(res))
            {
                res = pShellItem->BindToHandler(NULL, BHID_ThumbnailHandler, IID_PPV_ARGS(&pThumbProvider));
                if (SUCCEEDED(res))
                {
                    res = pThumbProvider->GetThumbnail(THUMBNAIL_SIZE, &mhBitmap, &wtsAlpha);
                    if (SUCCEEDED(res))
                    {
                        InitWindow();
                    }
                    else
                    {
                        mpLog->Console(SL_CODELOCATION, "GetThumbnail failed res=%ld", res);
                    }
                    pThumbProvider->Release();
                }
                else
                {
                    mpLog->Console(SL_CODELOCATION, "SHCreateItemFromParsingName failed res=%ld", res);
                }
                pShellItem->Release();
            } 
            else
            {
                mpLog->Console(SL_CODELOCATION, "BindToHandler failed res=%ld", res);
            }
            CoUninitialize();
        } 
        else
        {
            mpLog->Console(SL_CODELOCATION, "CoInitializeEx failed res=%ld", res);
        }
        MessageLoop();
    }

    void ThumbnailTest::InitWindow()
    {
        RECT winRect = { 0, 0, 300, 300 };
        WNDCLASSEX wcex = { 0 };
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;// | CS_OWNDC;
        wcex.lpfnWndProc = MyDefWindowProcW;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = mhInstance;
        wcex.hIcon = NULL;
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszClassName = L"ThumbnailTest";
        wcex.hIconSm = NULL;
        RegisterClassEx(&wcex);
        AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
        mhWindow = CreateWindow(L"ThumbnailTest", L"ThumbnailTest",
                                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,//WS_POPUP,
                                CW_USEDEFAULT, CW_USEDEFAULT, winRect.right-winRect.left, winRect.bottom-winRect.top,
                                NULL, NULL, mhInstance, NULL);
        if (mhWindow == nullptr)
        {
            mpLog->Console(SL_CODELOCATION, "CreateWindow failed!");
        }

        ::ShowWindow(mhWindow, SW_NORMAL);
        ::UpdateWindow(mhWindow);
    }

    void ThumbnailTest::MessageLoop()
    {
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    LRESULT CALLBACK ThumbnailTest::MyDefWindowProcW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        switch (Msg)
        {
        case WM_ACTIVATE:
            break;
        case WM_PAINT:
            OnPaintHandler(hWnd, Msg, wParam, lParam);
            break;
        case WM_DESTROY:
            OnDestroyHandler(hWnd, Msg, wParam, lParam);
            break;

        default:
            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }
        return 0;
    }

    void ThumbnailTest::OnPaintHandler(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        PAINTSTRUCT ps;
        HDC memDC = NULL;
        HDC hdc = BeginPaint(hWnd, &ps);

        TextOutW(hdc, 10, 10, L"ThumbnailTest Window", (int)wcsnlen(L"ThumbnailTest Window", 512));

        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
        SelectObject(hdc, hPen);
        Rectangle(hdc, 10, 30, THUMBNAIL_SIZE+10, THUMBNAIL_SIZE+30);
        DeleteObject(hPen);

        if (mpInstance->mhBitmap)
        {
            memDC = CreateCompatibleDC(hdc);
            SelectObject(memDC, mpInstance->mhBitmap);
            StretchBlt(hdc, 10, 30, THUMBNAIL_SIZE, THUMBNAIL_SIZE, memDC, 0, 0, THUMBNAIL_SIZE, THUMBNAIL_SIZE, SRCCOPY);
            //BitBlt(hdc, 10, 30, THUMBNAIL_SIZE, THUMBNAIL_SIZE, memDC, 0, 0, SRCCOPY);
        }

        BITMAP bitmapInfo = { 0 };
        GetObject(mpInstance->mhBitmap, sizeof(BITMAP), &bitmapInfo);

        printf_s("bitmapInfo = (%u, %u)\n", bitmapInfo.bmWidth, bitmapInfo.bmHeight);

        DeleteDC(memDC);
        EndPaint(hWnd, &ps);
    }

    void ThumbnailTest::OnDestroyHandler(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        DeleteObject(mpInstance->mhBitmap);
        mpInstance->mhBitmap = nullptr;

        PostQuitMessage(0);
    }
}

