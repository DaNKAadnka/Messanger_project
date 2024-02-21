#pragma once

#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class Tcp_listener {

public:

	Tcp_listener(std::string ipAdress, int port);
	~Tcp_listener();

	void CleanUp();

	void Send(int client_socket, std::string msg);

	void Run();


private:

	std::string m_ipAdress;
	int         m_port;

	// Initialze winsock
	WSADATA wsData;
	WORD ver;
	int erStat;

	
	// Bind the ip address and port to a socket
	sockaddr_in hint;
	SOCKET Create_Socket();
};
