#include "stdafx.h"

#include <iostream>

#define VLD_FORCE_ENABLE
#include <vld/vld.h>
#include <google/protobuf/stubs/common.h>

#include "Log.h"
#include <Utils/CodeLocation.h>
//-------------- GenericUtils --------------
#include "StringUtilTest.h"
#include "TimeUtilTest.h"
#include "DirectoryUtilTest.h"
#include "TestClassTest.h"
#include "UpPrivilegeTest.h"
#include "VersionUtilTest.h"
#include "ProcessUtilTest.h"
#include "ThumbnailTest.h"
#include "StdCppTest.h"
#include "StdStlTest.h"
#include "UnhandlerExceptionTest.h"
#include "WaitMultiEventTest.h"
#include "JsonTest.h"
#include "TinyXml2Test.h"
#include "MD5Test.h"
#include "WindowsInfoLookerTest.h"
#include "CryptogramTest.h"
#include "MySQLConnectionTest.h"
#include "RandomNumberTest.h"
//------------ LibCurl -------------
#include "LibcurlHttpTest.h"
//------------ ProtoBuf -------------
#include "UserInfoTest.h"
//------------ TcpUdpCommunication -------------
#include "TcpSocketServerTest.h"
#include "UdpSocketServerTest.h"

BOOL ConsoleEventHandler(DWORD dwCtrlType);

namespace HaHa
{
    template <typename T>
    struct Singleton
    {
    private:

        struct object_creator
        {
            // This constructor does nothing more than ensure that instance()
            //  is called before main() begins, thus creating the static
            //  T object before multithreading race issues can come up.
            object_creator(void)
            {
                std::cout << "object_creator::object_creator" << std::endl;
                Singleton<T>::instance();
            }

            inline void do_nothing(void) const {}
        };
        static object_creator create_object;

        Singleton(void);

    public:

        typedef T object_type;

        // If, at any point (in user code), singleton_default<T>::instance()
        //  is called, then the following function is instantiated.
        static object_type& instance(void)
        {
            // This is the object that we return a reference to.
            // It is guaranteed to be created before main() begins because of
            //  the next line.
            static object_type obj;

            // The following line does nothing else than force the instantiation
            //  of singleton_default<T>::create_object, whose constructor is
            //  called before main() begins.
            create_object.do_nothing();

            return obj;
        }
    };

    template <typename T>
    typename Singleton<T>::object_creator Singleton<T>::create_object;

    struct Hello
    {
        Hello(void) { std::cout << "Hello!" << std::endl; }
        ~Hello(void) { std::cout << "Goodbye!" << std::endl; }
    };


    template <typename T>
    struct SingletonUtil
    {
    private:
        static std::mutex      mInstanceMutex;
        static std::atomic<T*> mpInstance;

        struct DestructHellpper
        {
        public:
            DestructHellpper()
            {
                std::cout << "DestructHellpper::DestructHellpper()" << std::endl;
            }

            ~DestructHellpper()
            {
                std::cout << "DestructHellpper::~DestructHellpper()" << std::endl;
            }

            inline void do_nothing(void) const {}
        };
        static DestructHellpper mDestructHellper;

    public:
        virtual ~SingletonUtil()
        {
            std::cout << "SingletonUtil()::~SingletonUtil()" << std::endl;
        }

        static T* GetInstance()
        {
            mDestructHellper.do_nothing();
            T *pInstance = mpInstance.load(std::memory_order_acquire);
            if (pInstance == nullptr)
            {
                std::lock_guard<std::mutex> lock(mInstanceMutex);
                pInstance = mpInstance.load(std::memory_order_relaxed);
                if (pInstance == nullptr)
                {
                    pInstance = new T();
                    mpInstance.store(pInstance, std::memory_order_release);
                }
            }

            return pInstance;
        }

    protected:
        SingletonUtil()
        {
            std::cout << "SingletonUtil()::SingletonUtil()" << std::endl;
        }

        SingletonUtil(const SingletonUtil& otherObj)
        {
            std::cout << "SingletonUtil()::SingletonUtil(const SingletonUtil& otherObj)" << std::endl;
        }

        SingletonUtil& operator = (const SingletonUtil& othrerObj)
        {
            std::cout << "SingletonUtil()::operator= return reference" << std::endl;
        }
    };

    class SigletonTest // : public SingletonUtil<SigletonTest>
    {
    public:
        ~SigletonTest() {}

    private:
        SigletonTest() {}

    private:
        friend SingletonUtil<SigletonTest>;

    public:
        void Entry()
        {
            std::cout << "void SigletonTest::Entry()" << std::endl;
        }
        void Exit();
    };

    template<typename T>
    std::atomic<T*> SingletonUtil<T>::mpInstance = nullptr;
    template<typename T>
    std::mutex      SingletonUtil<T>::mInstanceMutex;
    template<typename T>
    typename SingletonUtil<T>::DestructHellpper SingletonUtil<T>::mDestructHellper;
}

int main(int argc, char** argv)
{
    BOOL retValue = SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleEventHandler, TRUE);
    std::cout << "====================================== Main Testing ======================================" << std::endl;
    Shuanglong::Log *pLog = Shuanglong::Log::GetInstance();
    pLog->Console(SL_CODE_LOCATION, "LogTest tid=%u", GetCurrentThreadId());

    //---------------------- Json Testing ----------------------
    Shuanglong::Test::JsonTest::Entry();
    Shuanglong::Test::JsonTest::Exit();

    //---------------------- TinyXml2 Testing ----------------------
    Shuanglong::Test::TinyXml2Test::Entry();
    Shuanglong::Test::TinyXml2Test::Exit();

    //---------------------- MD5 Testing ----------------------
    Shuanglong::Test::MD5Test::Entry();
    Shuanglong::Test::MD5Test::Exit();

    //--------------------- GenericUtils Testing ---------------------
    //Shuanglong::TestClassTest::Entry();
    //Shuanglong::Test::StringUtilTest::Entry();
    //Shuanglong::Test::TimeUtilTest::Entry();
    Shuanglong::Test::DirectoryUtilTest::Entry();
    Shuanglong::Test::DirectoryUtilTest::Exit();
    //Shuanglong::Test::UpPrivilegeTest::Entry();
    //Shuanglong::Test::VersionUtilTest::Entry();
    //Shuanglong::Test::ProcessUtilTest::Entry();
    //Shuanglong::Test::ThumbnailTest::Entry();
    Shuanglong::Test::StdCppTest::Entry();
    Shuanglong::Test::StdStlTest::Entry();
    //Shuanglong::Test::UnhandlerExceptionTest::GetInstance();
    //Shuanglong::Test::WaitMultiEventTest::GetInstance()->Entry();
    //Shuanglong::Test::WaitMultiEventTest::GetInstance()->Exit();
    Shuanglong::Test::CryptogramTest::Entry();
    Shuanglong::Test::CryptogramTest::Exit();
    Shuanglong::Test::MySQLConnectionTest::Entry();
    Shuanglong::Test::MySQLConnectionTest::Exit();

    Shuanglong::Test::WindowsInfoLookerTest::GetInstance()->Entry();

    //Shell_NotifyIcon
    //FindFirstFile
    //FindFirstFile

    //--------------------- LibCurl Testing --------------------
    Shuanglong::Test::LibcurlHttpTest::GetInstance()->Entry();
    Shuanglong::Test::LibcurlHttpTest::GetInstance()->Exit();

    //--------------------- Protobuf Testing --------------------
    Shuanglong::Test::UserInfoTest::GetInstance()->Entry();
    Shuanglong::Test::UserInfoTest::GetInstance()->Exit();

    //--------------------- TcpUdpCommunication Testing ---------------------
    Shuanglong::Test::TcpSocketServerTest::Entry();
    Shuanglong::Test::UdpSocketServerTest::Entry();

    //------------------------ Random Number Testing ------------------------
    //Shuanglong::Test::RandomNumberTest::GetInstance()->Entry();
    //Shuanglong::Test::RandomNumberTest::GetInstance()->Exit();

    //HaHa::SigletonTest::GetInstance()->Entry();
    HaHa::SigletonTest *pTest = HaHa::SingletonUtil<HaHa::SigletonTest>::GetInstance();
    pTest->Entry();

    HaHa::Hello& hello = HaHa::Singleton<HaHa::Hello>::instance();
    HaHa::Hello& hello2 = HaHa::Singleton<HaHa::Hello>::instance();
    std::cout << &hello << " : " << &hello2 << std::endl;

    std::cout << "Press any key to exit !" << std::endl;
    getchar();

    Shuanglong::Test::TcpSocketServerTest::Exit();
    Shuanglong::Test::UdpSocketServerTest::Exit();

    SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleEventHandler, FALSE);

    google::protobuf::ShutdownProtobufLibrary(); // VLD ¼ì²âµ½ ProtoBuf ÄÚ´æÐ¹Â©£¨²¹³ä£ºrepeated ÀàÐÍ add_foo --> clear_foo£©
    return 0;
}

BOOL ConsoleEventHandler(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
    case CTRL_C_EVENT:
        printf_s("Control + C\n");
        Shuanglong::Test::UdpSocketServerTest::Exit();
        break;
    case CTRL_BREAK_EVENT:
        printf_s("Control + Break\n");
        break;
    case CTRL_CLOSE_EVENT:
        printf_s("Close\n");
        Shuanglong::Test::UdpSocketServerTest::Exit();
        break;
    case CTRL_LOGOFF_EVENT:
        printf_s("User is logging off\n");
        break;
    case CTRL_SHUTDOWN_EVENT:
        printf_s("The system is shutting down\n");
        break;
    default:
        break;
    }

    return FALSE;
}

