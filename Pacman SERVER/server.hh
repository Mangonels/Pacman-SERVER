//TCP SERVER source file
#pragma once
#include "SERVER connect.hh" //Contains all the header files we need
#include "IOManager.hh"
using namespace std;

void connect()
{
	int delay = 500;
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
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, NULL);

	sock_CONNECTION = socket(AF_INET, SOCK_STREAM, NULL);
	ADDRESS.sin_addr.s_addr = inet_addr("127.0.0.1");
	ADDRESS.sin_family = AF_INET;
	ADDRESS.sin_port = htons(5444);

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
			//mira si es para enviar datos o guardarlos

			cout << "\n\tA connection was found!" << endl;
			char MESSAGE[200];
			SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
			string charToString = MESSAGE;

			if (charToString == "GetInfo") {
				SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
				Player temp;
				temp.name = MESSAGE;
				temp = IOManager::GetPlayerData(temp); //crea un Player temporal para recoger todos los datos necesarios
				Sleep(delay);
				//score
				string score = to_string(temp.score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL); 
				//a1
				Sleep(delay);
				string a1 = to_string(temp.a1);
				SUCCESSFUL = send(sock_CONNECTION, a1.c_str(), 46, NULL); 
				//a2
				Sleep(delay);
				string a2 = to_string(temp.a2);
				SUCCESSFUL = send(sock_CONNECTION, a2.c_str(), 46, NULL); 
				//a3
				Sleep(delay);
				string a3 = to_string(temp.a3);
				SUCCESSFUL = send(sock_CONNECTION, a3.c_str(), 46, NULL); 
				//a4
				Sleep(delay);
				string a4 = to_string(temp.a4);
				SUCCESSFUL = send(sock_CONNECTION, a4.c_str(), 46, NULL); 
				//a5
				Sleep(delay);
				string a5 = to_string(temp.a5);
				SUCCESSFUL = send(sock_CONNECTION, a5.c_str(), 46, NULL); 
			}
			else if (charToString == "SaveData"){
				Player temp;
				string CONVERTER;
				//name
				SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
				CONVERTER = MESSAGE;
				temp.name = CONVERTER;
				//score
				SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
				CONVERTER = MESSAGE;
				temp.score = stoi(CONVERTER);
				//achievement1
				SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
				CONVERTER = MESSAGE;
				temp.a1 = stoi(CONVERTER);
				//achievement2
				SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
				CONVERTER = MESSAGE;
				temp.a2 = stoi(CONVERTER);
				//achievement3
				SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
				CONVERTER = MESSAGE;
				temp.a3 = stoi(CONVERTER);
				//achievement4
				SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
				CONVERTER = MESSAGE;
				temp.a4 = stoi(CONVERTER);
				//achievement5
				SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
				CONVERTER = MESSAGE;
				temp.a5 = stoi(CONVERTER);

				IOManager::InsertResultInOrder(temp);
				IOManager::SetPlayerData(temp);
			}
			else if (charToString == "GetRanking") {
				Sleep(delay);
				list<Player> temp;
				temp = IOManager::GetRanking();
				Player arrayTemp[10];

				int i = 0;

				for (std::list<Player>::iterator it = temp.begin(); it != temp.end(); ++it) {
					arrayTemp[i].name = it->name;
					arrayTemp[i].score = it->score;
					i++;
				}
				
				int j = 0;
				//rank1
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				string score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank2
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(500);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank3
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank4
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank5
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank6
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank7
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank8
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank9
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);

				//rank10
					//name
				SUCCESSFUL = send(sock_CONNECTION, arrayTemp[j].name.c_str(), 46, NULL);
				Sleep(delay);
					//score
				score = to_string(arrayTemp[j].score);
				SUCCESSFUL = send(sock_CONNECTION, score.c_str(), 46, NULL);
				j++;
				Sleep(delay);
			}
		}
	}
}