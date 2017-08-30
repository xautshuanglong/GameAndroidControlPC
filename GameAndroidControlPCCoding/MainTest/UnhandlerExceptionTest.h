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
            DestructHellpper();
            ~DestructHellpper();
        };
        static DestructHellpper mDestructHellper;

    private:
    public:
        void InitializeHandler();
        void UninitializeHandler();
        static UnhandlerExceptionTest* GetInstance();
    };
}
