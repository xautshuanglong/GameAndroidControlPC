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

        class SingleHelpper
        {
        public:
            SingleHelpper();
            ~SingleHelpper();
        };
        static SingleHelpper         mHelpper;

    public:
        ~MultiThreadTest();
        static void Entry();

    private:
    };
}
