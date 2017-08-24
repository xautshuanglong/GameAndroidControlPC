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

//------------ TcpUdpCommunication -------------
#include "TcpSocketServerTest.h"
#include "UdpSocketServerTest.h"

BOOL ConsoleEventHandler(DWORD dwCtrlType);

int main(int argc, char** argv)
{
    BOOL retValue = SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleEventHandler, TRUE);
    std::cout << "====================================== Main Testing ======================================" << std::endl;
    ShuangLong::Log *pLog = ShuangLong::Log::GetInstance();

    //--------------------- GenericUtils Testing ---------------------

    //ShuangLong::TestClassTest::Entry();
    //ShuangLong::Test::StringUtilTest::Entry();
    //ShuangLong::Test::TimeUtilTest::Entry();
    //ShuangLong::Test::DirectoryUtilTest::Entry();
    //ShuangLong::Test::UpPrivilegeTest::Entry();
    //ShuangLong::Test::VersionUtilTest::Entry();
    //ShuangLong::Test::ProcessUtilTest::Entry();
    ShuangLong::Test::ThumbnailTest::Entry();

    //--------------------- TcpUdpCommunication Testing ---------------------

    //ShuangLong::Test::TcpSocketServerTest::Entry();
    //ShuangLong::Test::UdpSocketServerTest::Entry();

    SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleEventHandler, FALSE);

    return 0;
}

BOOL ConsoleEventHandler(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
    case CTRL_C_EVENT:
        printf_s("Control + C\n");
        break;
    case CTRL_BREAK_EVENT:
        printf_s("Control + Break\n");
        break;
    case CTRL_CLOSE_EVENT:
        printf_s("Close\n");
        ShuangLong::Test::UdpSocketServerTest::Exit();
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

