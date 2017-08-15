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

int main(int argc, char** argv)
{
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
    //ShuangLong::Test::ThumbnailTest::Entry();

    //--------------------- TcpUdpCommunication Testing ---------------------

    ShuangLong::Test::TcpSocketServerTest::Entry();

    return 0;
}