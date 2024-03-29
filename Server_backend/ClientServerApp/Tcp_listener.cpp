#include "Tcp_listener.h"
#include "p_controller.h"
#include <sstream>
#include <vector>

Tcp_listener::Tcp_listener (std::string ipAdress, int port) : m_ipAdress(ipAdress), m_port(port) {
	
	m_ipAdress = ipAdress;
	m_port = port;

	ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cout << "Can't Initialize winsock! Quitting" << std::endl;
		return;
	}
}

Tcp_listener::~Tcp_listener() {

	CleanUp();
}

void Tcp_listener::CleanUp() {

	WSACleanup();
}

SOCKET Tcp_listener::Create_Socket() {

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cout << "Can't create a socket! Quitting" << std::endl;
		return INVALID_SOCKET;
	}

	in_addr ip_address;
	erStat = inet_pton(AF_INET, m_ipAdress.c_str(), &ip_address);

	hint.sin_family = AF_INET;
	hint.sin_port   = htons(1234);
	hint.sin_addr   = ip_address; 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	listen(listening, SOMAXCONN);
	std::cout << "Listening\n";

	return listening;
}


void Tcp_listener::Send (int client_socket, std::string msg) {

	send(client_socket, msg.c_str(), msg.size() + 1, 0);
}





// Main functional

void Tcp_listener::Run() {

	p_controller p_c;


	SOCKET server_socket = Create_Socket();
	if (server_socket == INVALID_SOCKET) {
		return;
	}

	// Create the master file descriptor set and zero it
	fd_set master{};
	
	FD_ZERO(&master);
	FD_SET(server_socket, &master);

	while (true) {

		
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{

			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication
			if (sock == server_socket)
			{
				// Accept a new connection
				SOCKET client_socket = accept(server_socket, nullptr, nullptr);

				if (client_socket != INVALID_SOCKET) {

					// Add the new connection to the list of connected clients
					FD_SET(client_socket, &master);

					// Send a welcome message to the connected client
					std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
					Send(client_socket, p_c.sendProtocolMessage(welcomeMsg));
				}

			}
			else // It's an inbound message
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				// Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					std::string message = std::string(buf, 0, bytesIn);
					std::cout << message << "\n";

					std::string response = p_c.processData(message);

					std::cout << "response:\n" << response << "\n------\n";

					std::istringstream ss(response);

					std::string line;
					std::vector <std::string> lines;
					while (getline(ss, line, '\n')) {
						lines.push_back(line);
					}
					std::string command = lines[0].erase(0, 8);
					std::string status = lines[1].erase(0, 7);


					// Bad practice, we are losing MVC 
					// However, it`s too tricky for me
					// Maybe I should use controller as main runner
					if (command == "Send Message" && status == "Success") {
						
						for (int j = 0; j < master.fd_count; j++)
						{
							SOCKET outSock = master.fd_array[j];
							if (outSock != server_socket)
							{
								std::cout << "send to other - response: " << response << "\n";
								Send(outSock, response);
							}
						}
					}
					else {
						Send(sock, response);
					}

					
				}
			}
		}
	}

	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	FD_CLR(server_socket, &master);
	closesocket(server_socket);

	// Message to let users know what's happening.
	std::string msg = "Server is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)
	{
		// Get the socket number
		SOCKET sock = master.fd_array[0];

		// Send the goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &master);
		closesocket(sock);
	}
}