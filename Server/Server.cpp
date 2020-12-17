#include "Server.h"

UDPClientServer::Server::Server(ULONG address, USHORT port) : m_Port(port), m_Address(address)
{
    cout << "Starting server" << endl;

    m_Version = MAKEWORD(2, 2);

    if (WSAStartup(m_Version, &m_Data) != 0)
    {
        throw runtime_error("Can't start WinSock: " + WSAGetLastError());
    }

    m_Socket = socket(AF_INET, SOCK_DGRAM, 0);

    m_AddressInfo.sin_addr.S_un.S_addr = address;
    m_AddressInfo.sin_family = AF_INET;
    m_AddressInfo.sin_port = port;

    if (bind(m_Socket, (sockaddr*)&m_AddressInfo, sizeof(m_AddressInfo)) == SOCKET_ERROR)
    {
        throw runtime_error("Can't bind socket: " + WSAGetLastError());
    }

}

UDPClientServer::Server::~Server()
{
    cout << "Stopping server" << endl;

    closesocket(m_Socket);
    WSACleanup();
}

SOCKET UDPClientServer::Server::getSocket() const
{
    return m_Socket;
}

USHORT UDPClientServer::Server::getPort() const
{
    return m_Port;
}

ULONG UDPClientServer::Server::getAddress() const
{
    return m_Address;
}
