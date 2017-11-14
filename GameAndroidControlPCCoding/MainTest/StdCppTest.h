#pragma once

#include "Log.h"

namespace Shuanglong::Test
{
    class StdCppTest sealed
    {
    private:
        Log*                    mpLog;
        const char             *mpName;
        static std::future<int>        mRetFuture;
        static StdCppTest      *mpInstance;

        class SingleHelpper
        {
        public:
            SingleHelpper();
            ~SingleHelpper();
        };
        static SingleHelpper    mHelpper;

    public:
        ~StdCppTest();
        static void Entry();

    private:
        StdCppTest();
        StdCppTest(const char* name);
        void StdStringFormatTest();
        void SharedPointerTypedefTest();
        void SharedPointerHelperFunc();
        void StdAsyncFuturePromiseTest(std::future<int>& futureRes);
    };
}
