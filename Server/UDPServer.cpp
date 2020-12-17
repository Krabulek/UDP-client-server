#include <iostream>
#include <csignal>
#include "server.h"

#define SERVER_PORT 54000


namespace
{
    const int BUF_SIZE = 1024;
    volatile sig_atomic_t do_shutdown = 0;
}

void signalHandler(int signum)
{
    cout << "Interrupt signal (" << signum << ") received.\n";
    do_shutdown = 1;
}

int main()
{
    long msgCounter = 0;

    signal(SIGINT, signalHandler);

    UDPClientServer::Server server(ADDR_ANY, htons(SERVER_PORT));

    sockaddr_in client;
    int clientLength = sizeof(client);

    char buffer[BUF_SIZE];

    while (!do_shutdown)
    {
        ZeroMemory(&client, clientLength);
        ZeroMemory(buffer, BUF_SIZE);

        int bytesIn = recvfrom(server.getSocket(), buffer, BUF_SIZE, 0, (sockaddr*)&client, &clientLength);
        if (bytesIn == SOCKET_ERROR)
        {
            cout << "Error receiving message from client: " << WSAGetLastError() << endl;
            continue;
        }
        cout << "Message received from client -> " << buffer << endl;

        msgCounter += 1;
    }

    server.~Server();

    cout << "Message counter: " << msgCounter << endl;

    system("pause");

    return 0;
}