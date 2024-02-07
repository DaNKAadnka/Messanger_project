#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

void quick_close(SOCKET& sock) {
    closesocket(sock);
    WSACleanup();
} 

int main() {

    WSADATA wsData;

    int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

    if (erStat != 0) {
        std::cout << "Error WinSock version initialization\n" << std::endl;
        std::cout << WSAGetLastError() << std::endl;
        return 1;
    }
    else {
        std::cout << "WinSock initialization is OK" << std::endl;
    }

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        std::cout << "Socket initialization error" << std::endl;
        quick_close(client_socket);
        return 1;
    }
    else {
        std::cout << "Socket initialization success" << std::endl;
    }

    sockaddr_in  serv_info;
    ZeroMemory(&serv_info, sizeof(serv_info));

    in_addr ip_serv_sock;
    erStat = inet_pton(AF_INET, "127.0.0.1", &ip_serv_sock);
    if (erStat <= 0) {
        std::cout << "Error in IP translation to specific format" << std::endl;
        quick_close(client_socket);
        return 1;
    }
    
    serv_info.sin_family = AF_INET;
    serv_info.sin_port = htons(1234);
    serv_info.sin_addr = ip_serv_sock;

    erStat = connect(client_socket, (sockaddr*)&serv_info, sizeof(serv_info));
    if (erStat != 0) {
        std::cout << "Connection to server is FAILED. " << WSAGetLastError() << std::endl;
        quick_close(client_socket);
        return 1;
    }
    else {
        std::cout << "Connected to server" << std::endl;
    }


}