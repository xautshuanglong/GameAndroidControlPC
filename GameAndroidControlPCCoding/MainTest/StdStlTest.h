#pragma once

#include "Log.h"

namespace Shuanglong::Test
{
    class StdStlTest sealed
    {
    private:
        Log*                    mpLog;
        static StdStlTest      *mpInstance;

        class SingleHelpper
        {
        public:
            SingleHelpper();
            ~SingleHelpper();
        };
        static SingleHelpper    mHelpper;

    public:
        ~StdStlTest();
        static void Entry();

    private:
        StdStlTest();
        void StdListTestUnique();
        void StdListTestFind();
    };
}
