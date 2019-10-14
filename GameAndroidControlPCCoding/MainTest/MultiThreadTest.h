#pragma once

namespace Shuanglong
{
    class Log;
}

namespace Shuanglong::Test
{
    class MultiThreadTest sealed
    {
    private:
        MultiThreadTest();
        Log*                         mpLog;
        static MultiThreadTest      *mpInstance;

        static int                   mgCountCommon;
        static std::atomic<int>      mgCountAtomic;

        class SingleHelpper
        {
        public:
            SingleHelpper();
            ~SingleHelpper();
        };
        static SingleHelpper         mHelpper;

    public:
        ~MultiThreadTest();
        static MultiThreadTest* GetInstance();
        void Entry();

    private:
        void ThreadCommon_Test();
        void ThreadAtomic_Test();
        static void ThreadFunc_Common();
        static void ThreadFunc_Atomic();
    };
}
