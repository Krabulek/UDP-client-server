#include "Client.h"

UDPClientServer::Client::Client(const string& name, int serverPort) : m_Name(name), m_ServerPort(serverPort)
{
    m_Version = MAKEWORD(2, 2);

    if (WSAStartup(m_Version, &m_Data) != 0)
    {
        throw runtime_error("Can't start WinSock: " + WSAGetLastError());
    }

    m_ServerAddressInfo.sin_family = AF_INET;
    m_ServerAddressInfo.sin_port = htons(serverPort);
    inet_pton(AF_INET, LOCAL_HOST, &m_ServerAddressInfo.sin_addr);

    m_Socket = socket(AF_INET, SOCK_DGRAM, 0);

}

UDPClientServer::Client::~Client()
{
    cout << "Stopping client: " << m_Name << endl;

    closesocket(m_Socket);
    WSACleanup();
}

SOCKET UDPClientServer::Client::getSocket() const
{
    return m_Socket;
}

sockaddr_in UDPClientServer::Client::getServerAddressInfo()
{
    return m_ServerAddressInfo;
}

string UDPClientServer::Client::getName()
{
    return m_Name;
}

string UDPClientServer::Client::getMsg(int seed)
{
    srand(time(0) + seed);
    return string(m_Name + ": " + to_string(rand()));
}
