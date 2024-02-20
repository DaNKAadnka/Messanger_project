#include <iostream>

#include "Tcp_listener.h"

using namespace std;


void main()
{
	setlocale(LC_ALL, "Russian");
	
	Tcp_listener tcp_server("127.0.0.1", 1234);

	tcp_server.Run();


	system("pause");

}