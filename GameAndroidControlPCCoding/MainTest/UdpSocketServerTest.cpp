#include "stdafx.h"
#include "UdpSocketServerTest.h"

namespace Shuanglong::Test
{
    UdpSocketServerTest* UdpSocketServerTest::mpInstance = nullptr;

    UdpSocketServerTest::UdpSocketServerTest()
        : mLogServer()
        , mListenRuningFlag(false)
        , mpListenThread(nullptr)
    {
    }

    UdpSocketServerTest::~UdpSocketServerTest()
    {
    }

    void UdpSocketServerTest::Entry()
    {
        mpInstance = new UdpSocketServerTest();
        mpInstance->mpLog = Log::GetInstance();

        std::cout << "---------------------------------- UdpSocketServerTest ----------------------------------" << std::endl;

        //mpInstance->Initialize();
    }

    void UdpSocketServerTest::Exit()
    {
        if (mpInstance != nullptr)
        {
            mpInstance->StopListen();
        }
    }

    void UdpSocketServerTest::Initialize()
    {
        WSADATA wsaData;

        Socket::SocketServer::WSAStartup(MAKEWORD(2, 2), &wsaData);

        mpInstance->StartListen();

        if (mpInstance->mpListenThread != nullptr &&
            mpInstance->mpListenThread->joinable())
        {
            mpInstance->mpListenThread->join();
        }

        Socket::SocketServer::WSACleanup();
    }

    void UdpSocketServerTest::ListenThreadFunc(void *param)
    {
        UdpSocketServerTest* pServer = (UdpSocketServerTest*)param;
        sockaddr_in          remoteSockAddress;
        int addressLen = sizeof(remoteSockAddress);
        SOCKET connectSocket = INVALID_SOCKET;
        char msgBuff[1024] = { 0 };
        int recvBytes = 0;

        pServer->mListenRuningFlag = true;
        while (pServer->mListenRuningFlag)
        {
            recvBytes = pServer->mLogServer.RecvFromSocket(msgBuff, 1024, 0, (SOCKADDR*)&remoteSockAddress, &addressLen);
            if (recvBytes > 0)
            {
                printf_s("%s", msgBuff);
            }
            else
            {
                printf_s("receive null -------\n");
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(3));
        }

        mpInstance->mpLog->Console(SL_CODELOCATION, "Exit recv thread ---- ");
    }

    void UdpSocketServerTest::StartListen()
    {
        if (mpListenThread != nullptr)
        {
            mLogServer.CloseSocket();
            mpListenThread->detach();
            delete mpListenThread;
            mpListenThread = nullptr;
        }

        mLogServer.CreateSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        mLogServer.BindSocket();

        mpListenThread = new std::thread(ListenThreadFunc, this);
    }

    void UdpSocketServerTest::StopListen()
    {
        mListenRuningFlag = false;
        if (mpListenThread != nullptr)
        {
            mpLog->Console(SL_CODELOCATION, "Before ShutdownSocket ---- ");
            //mLogServer.ShutdownSocket(SD_BOTH);
            mLogServer.CloseSocket();

            //std::this_thread::sleep_for(std::chrono::milliseconds(1));

            //mpLog->Console(SL_CODELOCATION, "After ShutdownSocket ---- ");
            //if (mpListenThread->joinable())
            //{
            //    mpLog->Console(SL_CODELOCATION, "Joining ---- ");
            //    mpListenThread->join();
            //    mpLog->Console(SL_CODELOCATION, "After joining ---- ");
            //}

            mpListenThread->detach();

            delete mpListenThread;
            mpListenThread = nullptr;

            mpLog->Console(SL_CODELOCATION, "Delete Over ---- ");
        }
    }
}
