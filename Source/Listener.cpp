#include <iostream>
#include <string>
#include "Headers/Argparse.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

int main(int argc, char* args[])
{	
	if (argc >= 2)
		return argparse(argc, args);
	else 
	{
		std::cout << "At least One Argument should be passed";
		return 0;
	}

}

std::string Listen()
{
	WSADATA wsData;
	int iResult;
	
	iResult = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return nullptr;
	}

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		printf("Cant create a socket..Quitting");
		return nullptr;
	}
	
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, SOMAXCONN);

	sockaddr_in client;
	int clientsize = sizeof(client);
	SOCKET clientsocket = accept(listening, (sockaddr*)&client, &clientsize);

	if (clientsocket == INVALID_SOCKET)
	{
		std::cout << "cannot connect to client" << std::endl;
		return nullptr;
	}

	char host[NI_MAXHOST];
	char service[NI_MAXHOST];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << "Connected on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " Connected on port " << ntohs(client.sin_port) << std::endl;

	}

	closesocket(listening);
	char buf[4096];
	
	while (true)
	{
		ZeroMemory(buf, 4096);
		int bytesreveived = recv(clientsocket, buf, 4096, 0);

		if (bytesreveived == SOCKET_ERROR)
		{
			std::cout << "Client disconnected" << std::endl;
			break;
		}

		send(clientsocket, buf, bytesreveived + 1, 0);
	}

	closesocket(clientsocket);
	WSACleanup();

}