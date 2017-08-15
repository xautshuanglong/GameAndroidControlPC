#include "stdafx.h"
#include "SocketServer.h"

namespace ShuangLong::Socket
{
    SocketServer::SocketServer()
    {
        int res = 0;
        ULONG binAddress = 0;

        res = inet_pton(AF_INET, "127.0.0.1", &binAddress);
        if (res == 0)
        {
            // IP µÿ÷∑Œﬁ–ß
        }
        else if (res == -1)
        {
            int errorCode = WSAGetLastError();
            printf_s("SocketServer.cpp CreateSocket failed errorCode=%d\n", errorCode);
        }

        mServerAddress.sin_family = AF_INET;
        mServerAddress.sin_addr.s_addr = binAddress;
        mServerAddress.sin_port = htons(27016);
    }

    SocketServer::~SocketServer()
    {
    }

    void SocketServer::CreateSocket(_In_ int addressFamily, _In_ int socketType, _In_ int protocol)
    {
        int errorCode = 0;
        mListenSocket = ::socket(addressFamily, socketType, protocol);
        if (mListenSocket == INVALID_SOCKET)
        {
            errorCode = WSAGetLastError();
            printf_s("SocketServer.cpp CreateSocket failed errorCode=%d\n", errorCode);
        }
    }

    void SocketServer::BindSocket()
    {
        int errorCode = 0;
        if (SOCKET_ERROR == ::bind(mListenSocket, (SOCKADDR*)&mServerAddress, sizeof(mServerAddress)))
        {
            errorCode = WSAGetLastError();
            printf_s("SocketServer.cpp BindSocket failed errorCode=%d\n", errorCode);
        }
    }

    void SocketServer::ListenSocket()
    {
        int errorCode = 0;
        if (SOCKET_ERROR == ::listen(mListenSocket, SOMAXCONN))
        {
            errorCode = WSAGetLastError();
            printf_s("SocketServer.cpp ListenSocket failed errorCode=%d\n", errorCode);
        }
    }

    SOCKET SocketServer::AcceptSocket(_Out_ struct sockaddr *pAddress, _Out_ int *pAddressLen)
    {
        int errorCode = 0;
        SOCKET retValue = INVALID_SOCKET;

        retValue = ::accept(mListenSocket, pAddress, pAddressLen);
        if (retValue == INVALID_SOCKET)
        {
            errorCode = WSAGetLastError();
            printf_s("SocketServer.cpp AcceptSocket failed errorCode=%d\n", errorCode);
        }

        return retValue;
    }

    void SocketServer::CloseSocket()
    {
        int errorCode = 0;
        if (SOCKET_ERROR == ::closesocket(mListenSocket))
        {
            errorCode = WSAGetLastError();
            printf_s("SocketServer.cpp CloseSocket failed errorCode=%d\n", errorCode);
        }
    }

    void SocketServer::ShutdownSocket(_In_ int how)
    {
        int errorCode = 0;
        if (SOCKET_ERROR == ::shutdown(mListenSocket, how))
        {
            errorCode = WSAGetLastError();
            printf_s("SocketServer.cpp ShutdownSocket failed errorCode=%d\n", errorCode);
        }
    }

    void SocketServer::WSAStartup(_In_ WORD wVersionRequested, _Out_ LPWSADATA lpWSAData)
    {
        ::WSAStartup(wVersionRequested, lpWSAData);
    }

    void SocketServer::WSACleanup()
    {
        ::WSACleanup();
    }
}

