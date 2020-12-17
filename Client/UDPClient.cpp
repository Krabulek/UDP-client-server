#include <iostream>
#include <csignal>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

#include "Client.h"

#define SERVER_PORT 54000

namespace
{
	volatile sig_atomic_t do_shutdown = 0;
}

void signalHandler(int signum)
{
	cout << "Interrupt signal (" << signum << ") received.\n";
	do_shutdown = 1;
}

void createAndRunClient(const string &name, const int& seed)
{
	UDPClientServer::Client client(name, SERVER_PORT);

	while (!do_shutdown)
	{
		sockaddr_in server = client.getServerAddressInfo();

		string msg = client.getMsg(seed);

		cout << "Sending: " << msg << endl;

		int sendOk = sendto(client.getSocket(), msg.c_str(), msg.size() + 1, 0, (sockaddr*)&server, sizeof(server));

		if (sendOk == SOCKET_ERROR)
		{
			cout << "Client sending error " << WSAGetLastError() << endl;
		}

		Sleep(4000);
	}

	client.~Client();
}

int main()
{
	signal(SIGINT, signalHandler);

	vector<string> clientNames = {
	  "Client1",
	  "Client2",
	  "Client3",
	  "Client4"
	};

	vector<thread> clients;

	for (int i = 0; i < clientNames.size(); i++)
	{
		clients.push_back(thread(createAndRunClient, clientNames[i], i*i));
	}

	for (auto& clt : clients) {
		clt.join();
	}
	
	return 0;
}