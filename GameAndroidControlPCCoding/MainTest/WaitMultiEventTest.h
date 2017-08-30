#pragma once

#include "Log.h"

namespace Shuanglong::Test
{
    class WaitMultiEventTest sealed
    {
    private:
        volatile bool                                  mIsWaitingFlag;
        HANDLE                                         mhEventConnected;
        HANDLE                                         mhEventDisconnected;
        Log                                           *mpLog;
        static std::mutex                              mMutexInstance;
        static std::atomic<WaitMultiEventTest*>        mpInstance;
        WaitMultiEventTest();
        ~WaitMultiEventTest();

        class DestructHellpper
        {
        public:
            DestructHellpper();
            ~DestructHellpper();
        };
        static DestructHellpper mDestructHellper;

    private:
        void WaitForMultiObjectsTest();

    public:
        void Entry();
        void Exit();
        static WaitMultiEventTest* GetInstance();
    };
}
