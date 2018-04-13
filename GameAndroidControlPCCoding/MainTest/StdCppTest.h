#pragma once

#include "Log.h"

namespace Shuanglong::Test
{
    class StdCppTest sealed
    {
    private:
        Log*                           mpLog;
        const char                    *mpName;
        static std::future<int>        mRetFuture;
        static StdCppTest             *mpInstance;

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
        void NestedClassTest();
    };

    class OuterClass
    {
    private:
        int mOutPrivateTest;

    public:
        int mOutPublicTest;
        void OuterClassFuncTest()
        {
            mOutPrivateTest = 30;
            mOutPublicTest = 40;
            std::cout << "OuterClass::OuterClassFuncTest(" << this << ")  InnerClass::mInPublicTest:" << mOutPublicInnerObj.mInPublicTest << std::endl;
        }

        class InnerClass
        {
        private:
            int mInPrivateTest;
        public:
            int mInPublicTest;

            InnerClass()
                : mInPrivateTest(0)
                , mInPublicTest(0)
            {
            }

            void InnerClassFuncTest()
            {
                OuterClass *pParentPtr = (OuterClass*)((char*)this-offsetof(OuterClass, mOutPublicInnerObj));
                pParentPtr->mOutPrivateTest = 50;
                pParentPtr->mOutPublicTest = 60;

                mInPrivateTest = 10;
                mInPublicTest = 20;
                std::cout << "InnerClass::InnerClassFuncTest  mInPrivateTest:" << mInPrivateTest
                    << "  mInPublicTest:" << mInPublicTest
                    << "  OuterClass::mOutPrivateTest" << pParentPtr->mOutPrivateTest
                    << "  OuterClass::mOutPublicTest" << pParentPtr->mOutPublicTest << std::endl;
            }
        };
        InnerClass mOutPublicInnerObj;
    };
}
