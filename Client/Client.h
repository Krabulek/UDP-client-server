#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <ctime>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define LOCAL_HOST "127.0.0.1"

using namespace std;

namespace UDPClientServer
{

    class Client
    {
    public:
        Client(const string& name, int serverPort);
        ~Client();

        SOCKET getSocket() const;
        sockaddr_in getServerAddressInfo();

        string getName();
        string getMsg(int seed);

    private:
        WSADATA m_Data;
        WORD m_Version;
        SOCKET m_Socket;
        sockaddr_in m_ServerAddressInfo;
        int  m_ServerPort;

        string m_Name;
    };

}

#endif