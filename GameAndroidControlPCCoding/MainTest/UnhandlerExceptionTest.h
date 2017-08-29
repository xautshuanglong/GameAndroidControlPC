#pragma once

namespace Shuanglong::Test
{
    class UnhandlerExceptionTest sealed
    {
    private:
        static std::mutex                                       mMutexInstance;
        static std::atomic<UnhandlerExceptionTest*>             mpInstance;
        UnhandlerExceptionTest();
        ~UnhandlerExceptionTest();

        class DestructHellpper
        {
        public:
            DestructHellpper(){}
            ~DestructHellpper()
            {
                UnhandlerExceptionTest *pTemp = mpInstance.load(std::memory_order_acquire);
                if (pTemp != nullptr)
                {
                    delete pTemp;
                    pTemp = nullptr;
                    mpInstance.store(pTemp, std::memory_order_release);
                }
            }
        };
        static DestructHellpper mDestructHellper;

    private:
    public:
        void InitializeHandler();
        void UninitializeHandler();
        static UnhandlerExceptionTest* GetInstance();
    };
}
