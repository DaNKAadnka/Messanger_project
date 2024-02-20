#include "Tcp_listener.h"
#include "db_handler.h"
#include <sstream>

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
	hint.sin_port = htons(1234);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);
	std::cout << "Listening\n";

	

	return listening;
}


void Tcp_listener::Send (int client_socket, std::string msg) {

	send(client_socket, msg.c_str(), msg.size() + 1, 0);
}

void Tcp_listener::Run() {


	db_handler db("messanger_db");

	db.open_db();


	db.create_table_if_not_exists();
	// Testing info
	db.print_all_users();



	SOCKET server_socket = Create_Socket();
	if (server_socket == INVALID_SOCKET) {
		return;
	}

	// Create the master file descriptor set and zero it
	fd_set master{};
	FD_ZERO(&master);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	FD_SET(server_socket, &master);

	while (true) {

		
		fd_set copy = master;

		// See who's talking to us
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			// Makes things easy for us doing this assignment
			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication?
			if (sock == server_socket)
			{
				// Accept a new connection
				SOCKET client_socket = accept(server_socket, nullptr, nullptr);

				if (client_socket != INVALID_SOCKET) {

					// Add the new connection to the list of connected clients
					FD_SET(client_socket, &master);

					// Send a welcome message to the connected client
					std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
					Send(client_socket, welcomeMsg);
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


					// Parse message by our protocol

					/* Create SQL statement */


					// If command is send_message
					for (int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != server_socket && outSock != sock)
						{
							std::ostringstream ss;
							std::cout << "message: " << buf << "\n";
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							std::string strOut = ss.str();

							Send(outSock, strOut);
						}
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