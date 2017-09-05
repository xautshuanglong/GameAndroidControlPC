#include "stdafx.h"
#include "WaitMultiEventTest.h"

#define EVENT_CONNECTED     TEXT("event.connected")
#define EVENT_DISCONNECTED  TEXT("event.disconnected")

namespace Shuanglong::Test
{
    std::atomic<WaitMultiEventTest*> WaitMultiEventTest::mpInstance = nullptr;
    std::mutex                       WaitMultiEventTest::mMutexInstance;
    WaitMultiEventTest::DestructHellpper WaitMultiEventTest::mDestructHellper;

    WaitMultiEventTest::WaitMultiEventTest()
        : mpLog(nullptr)
        , mIsWaitingFlag(true)
    {
        std::cout << "WaitMultiEventTest::WaitMultiEventTest()" << std::endl;
    }

    WaitMultiEventTest::~WaitMultiEventTest()
    {
        std::cout << "WaitMultiEventTest::~WaitMultiEventTest()" << std::endl;
    }

    WaitMultiEventTest* WaitMultiEventTest::GetInstance()
    {
        WaitMultiEventTest *pTemp = mpInstance.load(std::memory_order_acquire);
        if (pTemp == nullptr)
        {
            std::lock_guard<std::mutex> lock(mMutexInstance);
            pTemp = mpInstance.load(std::memory_order_relaxed);
            if (pTemp == nullptr)
            {
                pTemp = new WaitMultiEventTest();
                mpInstance.store(pTemp, std::memory_order_release);
            }
        }

        return pTemp;
    }

    void WaitMultiEventTest::Entry()
    {
        std::cout << "----------------------------- WaitMultiEvent Testing -----------------------------" << std::endl;
        WaitMultiEventTest *pInstance = GetInstance();
        pInstance->mpLog = Log::GetInstance();

        pInstance->mpLog->Console(SL_CODELOCATION, "----- Entry");
        mhEventConnected = OpenEvent(SYNCHRONIZE, FALSE, EVENT_CONNECTED);
        if (mhEventConnected == NULL)
        {
            mpLog->Console(SL_CODELOCATION, "Before CreatEvent mhEventConnected");
            mhEventConnected = CreateEvent(NULL, FALSE, FALSE, EVENT_CONNECTED);
        }
        mhEventDisconnected = OpenEvent(SYNCHRONIZE, FALSE, EVENT_DISCONNECTED);
        if (mhEventDisconnected == NULL)
        {
            mpLog->Console(SL_CODELOCATION, "Before CreatEvent mhEventDisconnected");
            mhEventDisconnected = CreateEvent(NULL, FALSE, FALSE, EVENT_DISCONNECTED);
        }
        pInstance->WaitForMultiObjectsTest();
    }

    void WaitMultiEventTest::Exit()
    {
        if (mhEventConnected != INVALID_HANDLE_VALUE)
        {
            CloseHandle(mhEventConnected);
            mhEventConnected = INVALID_HANDLE_VALUE;
        }
        if (mhEventDisconnected != INVALID_HANDLE_VALUE)
        {
            CloseHandle(mhEventDisconnected);
            mhEventDisconnected = INVALID_HANDLE_VALUE;
        }
        (*mpInstance).mpLog->Console(SL_CODELOCATION, "----- Exit");
    }

    void WaitMultiEventTest::WaitForMultiObjectsTest()
    {
        if (mhEventConnected != INVALID_HANDLE_VALUE && mhEventDisconnected != INVALID_HANDLE_VALUE)
        {
            HANDLE events[] = { mhEventConnected, mhEventDisconnected };
            DWORD dwEvent = -1;
            int waitCount = 300;

            while (mIsWaitingFlag)
            {
                if (waitCount>=300)
                {
                    waitCount = 0;

                    dwEvent = WaitForMultipleObjects(_countof(events), events, false, 10);
                    switch (dwEvent)
                    {
                    case WAIT_OBJECT_0:
                        mpLog->Console(SL_CODELOCATION, "WAIT_OBJECT_0 connected signaled");
                        break;
                    case WAIT_OBJECT_0 + 1:
                        mpLog->Console(SL_CODELOCATION, "WAIT_OBJECT_1 disconnected signaled");
                        break;
                    case WAIT_TIMEOUT:
                        mpLog->Console(SL_CODELOCATION, "WAIT_TIMEOUT ------ ");
                        break;
                    default:
                        mpLog->Console(SL_CODELOCATION, "ErrorCOde = %u", GetLastError());
                        break;
                    }
                }
                else
                {
                    ++waitCount;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
        else
        {
            mpLog->Console(SL_CODELOCATION, "mhEvent == INVALID_HANDLE_VALUE");
        }
    }
}
