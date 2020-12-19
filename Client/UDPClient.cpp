#include <iostream>
#include <csignal>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

#include "Client.h"

#define MAX_NUM_CLIENTS 10
#define DEF_NUM_CLIENTS 2
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

	vector<string> clientBase = {
	  "Client1",
	  "Client2",
	  "Client3",
	  "Client4",
	  "Client5",
	  "Client6",
	  "Client7",
	  "Client8",
	  "Client9",
	  "Client10"
	};

	int numClients = DEF_NUM_CLIENTS;

	string sNumClients = "";
	cout << "Provide the number of clients, at most " << MAX_NUM_CLIENTS << endl;
	cin >> sNumClients;

	if (sNumClients.empty())
	{
		cout << "Number of clients wasn't provided, using default " << DEF_NUM_CLIENTS << endl;
	}
	else
	{
		try {
			numClients = stoi(sNumClients);

			if (numClients > MAX_NUM_CLIENTS)
			{
				numClients = MAX_NUM_CLIENTS;
				cout << "Sorry, you are asking for too much, I can give you only " << MAX_NUM_CLIENTS << endl;
			}
			cout << "Number of clients provided: " << numClients << endl;
		}
		catch (invalid_argument e) {
			cout << "What the heck? Just type in a number, it can't be so hard\n";
			exit(ERROR_INVALID_DATA);
		}
		
	}
	
	vector<thread> clients;

	for (int i = 0; i < numClients; i++)
	{
		clients.push_back(thread(createAndRunClient, clientBase[i], i*i));
	}

	for (auto& clt : clients) {
		clt.join();
	}
	
	return 0;
}