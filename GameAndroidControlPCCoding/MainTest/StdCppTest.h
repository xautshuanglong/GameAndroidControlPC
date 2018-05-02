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
        void OperatorNewAndDelete();
        void PlacementNewTest();
        void UnionStructTest();
        void RangeBasedForLoopTest();
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

    //************************************************************************\
    //    Author     : JiangChuanbiao
    //    Date       : 2018-4-17
    //    Description: 
    //        Tools -> Option -> C/C++ -> Command Line ->
    //        /d1reportSingleClassLayoutOverloadNew 
    //************************************************************************/
    class OverloadNew
    {
    private:
        int      mIntTest1;
        int      mIntTest2;

    public:
        OverloadNew()
        {
            std::cout << "OverloadNew::OverloadNew" << std::endl;
            mIntTest1 = 0x01020304;
            mIntTest2 = 0x05060708;
        }

        OverloadNew(int intTest)
        {
            std::cout << "OverloadNew::OverloadNew(int intTest)  intTest=" << intTest << std::endl;
            this->mIntTest1 = intTest;
        }

        ~OverloadNew()
        {
            std::cout << "OverloadNew::~OverloadNew" << std::endl;
        }

        virtual void VirtualFuncTest()
        //void VirtualFuncTest()
        {
            std::cout << "OverloadNew::VirtualFuncTest()" << std::endl;
        }

        void* operator new(size_t size)
        {
            std::cout << "OverloadNew::new(size_t size) size=" << size << std::endl;
            return ::operator new(size);
        }

        void operator delete (void* pointee)
        {
            std::cout << "OverloadNew::delete(void* pointee)" << std::endl;
            ::operator delete(pointee);
        }

        void* operator new[] (size_t size)
        {
            std::cout << "OverloadNew::new[](size_t size) size=" << size << std::endl;
            return ::operator new[](size);
        }

        void operator delete[] (void* pointee)
        {
            std::cout << "OverloadNew::delete[](void* pointee)" << std::endl;
            ::operator delete[](pointee);
        }

        void* operator new(size_t size, std::string strTest)
        {
            std::cout << "OverloadNew::new(size_t size, std::string strTest) size=" << size << " -----> with string:" << strTest << std::endl;
            return ::operator new(size);
        }

        void operator delete (void* pointee, std::string strTest)
        {
            std::cout << "OverloadNew::delete(void* pointee, std::string strTest)" << strTest << " -----> with string:" << strTest << std::endl;
            ::operator delete(pointee);
        }

        void* operator new(size_t size, void* pBuffer)
        {
            std::cout << "OverloadNew::new(size_t size, void* pBuffer) size=" << size << " -----> BufferAddress:" << pBuffer << std::endl;
            if (pBuffer != nullptr)
            {
                return ::operator new(size, pBuffer);
            }
            return ::operator new(size);
        }

        void operator delete (void* pointee, void* pBuffer)
        {
            std::cout << "OverloadNew::delete(void* pointee, void* pBuffer)" << " -----> BufferAddress:" << pBuffer << std::endl;
            ::operator delete(pointee);
        }
    };

    //************************************************************************\
    //    Author     : JiangChuanbiao
    //    Date       : 2018-4-17
    //    Description: Placement new testing
    //************************************************************************/
    class PlacementNew
    {
    private:
        int     mIntTest1;
        int     mIntTest2;

    public:
        PlacementNew()
        {
            std::cout << "PlacementNew::PlacementNew()" << std::endl;
            mIntTest1 = 0x01020304;
            mIntTest2 = 0x05060708;
        }

        ~PlacementNew()
        {
            std::cout << "PlacementNew::~PlacementNew()" << std::endl;
        }

        virtual void VirtualFunTest()
        {
            std::cout << "PlacementNew::VirtualFunTest()" << std::endl;
        }
    };
}
