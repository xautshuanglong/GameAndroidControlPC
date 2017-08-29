#include "stdafx.h"

#include <iostream>

#include "Log.h"

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
#include "UnhandlerExceptionTest.h"
#include "WaitMultiEventTest.h"

//------------ TcpUdpCommunication -------------
#include "TcpSocketServerTest.h"
#include "UdpSocketServerTest.h"

BOOL ConsoleEventHandler(DWORD dwCtrlType);

int main(int argc, char** argv)
{
    BOOL retValue = SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleEventHandler, TRUE);
    std::cout << "====================================== Main Testing ======================================" << std::endl;
    Shuanglong::Log *pLog = Shuanglong::Log::GetInstance();

    //--------------------- GenericUtils Testing ---------------------

    //Shuanglong::TestClassTest::Entry();
    //Shuanglong::Test::StringUtilTest::Entry();
    //Shuanglong::Test::TimeUtilTest::Entry();
    //Shuanglong::Test::DirectoryUtilTest::Entry();
    //Shuanglong::Test::UpPrivilegeTest::Entry();
    //Shuanglong::Test::VersionUtilTest::Entry();
    //Shuanglong::Test::ProcessUtilTest::Entry();
    //Shuanglong::Test::ThumbnailTest::Entry();
    //Shuanglong::Test::StdCppTest::Entry();

    //Shuanglong::Test::UnhandlerExceptionTest::GetInstance();
    Shuanglong::Test::WaitMultiEventTest::GetInstance()->Entry();
    Shuanglong::Test::WaitMultiEventTest::GetInstance()->Exit();

    //--------------------- TcpUdpCommunication Testing ---------------------

    //Shuanglong::Test::TcpSocketServerTest::Entry();
    //Shuanglong::Test::UdpSocketServerTest::Entry();

    SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleEventHandler, FALSE);

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

