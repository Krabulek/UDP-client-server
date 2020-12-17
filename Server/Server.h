#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <winsock2.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

namespace UDPClientServer
{
    class Server
    {
    public:
        Server(ULONG address, USHORT port);
        ~Server();

        SOCKET getSocket() const;
        USHORT getPort() const;
        ULONG getAddress() const;

    private:

        WSADATA m_Data;
        WORD m_Version;
        SOCKET m_Socket;
        sockaddr_in m_AddressInfo;
        USHORT  m_Port;
        ULONG m_Address;

    };

}

#endif