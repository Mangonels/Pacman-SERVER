//TCP SERVER source file

#include "SERVER connect.hh" //Contains all the header files we need

using namespace std;

void connect()
{
	//Some necesary local variables:
	long SUCCESSFUL; //Saves the WSAStartup inside of it.
	WSAData WinSockData; //Struct which saves data for WinSock
	WORD DLLVERSION; //Saves a version constructed with MAKEWORD

	//WORDS = objects of a data size that a processor naturally handles (such as 16 or 32-bit)
	DLLVERSION = MAKEWORD(2, 1); //macro to create WORD value by concatenating its arguments

	//WINSOCK DLL STARTUP:
	SUCCESSFUL = WSAStartup(DLLVERSION, &WinSockData); //In order to start up the Winsock Aplication Programming Enviroment, we need to specify the DLL version, and the memory direction towards a WSAData structure

	//Socket Structure
	SOCKADDR_IN ADDRESS; //Structure used for containing socket address information
	int AddressSize = sizeof(ADDRESS);

	//CREATE SOCKETS:
	SOCKET sock_LISTEN; //Socket which listens for incoming connection
	SOCKET sock_CONNECTION; //Socket which activates if a connection is found

	//Setting ADDRESS structure information:
	//socket Arguments: AF_INET = internet domain (not Unix domain),
	//SOCK_STREAM = connection orientated TCP (not SOCK_DGRAM)
	sock_CONNECTION = socket(AF_INET, SOCK_STREAM, NULL);
	ADDRESS.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set IP
	ADDRESS.sin_family = AF_INET;
	ADDRESS.sin_port = htons(444); //port

	sock_LISTEN = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sock_LISTEN, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));
	listen(sock_LISTEN, SOMAXCONN); //listen without limits
	//The listening socket "sock_LISTEN" is now listening to incomei
	
	//CHECKING IF "sock_LISTEN" found a connection:
	for (;;)
	{
		cout << "\n\tSERVER: Waiting for incoming connection...";
		if (sock_CONNECTION = accept(sock_LISTEN, (SOCKADDR*)&ADDRESS, &AddressSize))
		{
			cout << "\n\tA connection was found!" << endl;

			SUCCESSFUL = send(sock_CONNECTION, "Server connection established!", 46, NULL); //<-- ASI ES COMO SE ENVIA UN MENSAJE!!
		}
	}
}