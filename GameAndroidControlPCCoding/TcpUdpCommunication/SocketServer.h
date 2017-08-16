#pragma once

#include "TcpUdpDefines.h"

namespace ShuangLong::Socket
{
    //************************************************************************\
    //    Author     : JiangChuanbiao
    //    Date       : 2017-8-15
    //    Description: UDP socket ÍøÂçÍ¨ÐÅ
    //************************************************************************/
    class TCPUDP_EXPORT SocketServer
    {
    private:
        SOCKET          mListenSocket;
        sockaddr_in     mServerAddress;

    public:
        SocketServer();
        ~SocketServer();

        void CreateSocket(_In_ int addressFamily,
                            _In_ int socketType,
                            _In_ int protocol);
        void BindSocket();
        void ListenSocket();
        SOCKET AcceptSocket(_Out_ struct sockaddr *pAddress,
                            _Out_ int *pAddressLen);
        int RecvFromSocket(_Out_ char *outBuffer,
                            _In_ int bufLen,
                            _In_ int flags,
                            _Out_ struct sockaddr *pAddress,
                            _Out_ int *pAddressLen);
        void CloseSocket();
        void ShutdownSocket(_In_ int how);

        static void WSAStartup(_In_ WORD wVersionRequested,
                                _Out_ LPWSADATA lpWSAData);
        static void WSACleanup(void);
    };
}

