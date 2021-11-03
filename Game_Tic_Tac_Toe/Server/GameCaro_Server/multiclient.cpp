#include <iostream>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

#include "multiclient.h"
#include "database.h"

using namespace std;


multiclient::multiclient(int Port)
{
	this->PORT = Port;
}


void multiclient::Init()
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	/* Initialize winsock */
	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return;
	}
}


void multiclient::CreateSocket()
{
	/* Create a socket */
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return;
	}
}


void multiclient::BindIpAddr()
{
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton ....

	/* Bind the IP address and port to a socket */
	bind(listening, (sockaddr*)&hint, sizeof(hint));

}


void multiclient::CreateMaster()
{
	FD_ZERO(&master);
}


void multiclient::Listening()
{
	/* Tell Winsock the socket is for listening */
	listen(listening, SOMAXCONN);

	/* Assign socket connected on master */
	FD_SET(listening, &master);

	bool running = true;

	while (running)
	{
		fd_set copy = master;

		/* See who's talking to us */
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		/* Loop through all the current connections */
		for (int i = 0; i < socketCount; i++)
		{
			/* Get a socket in copy */ 
			SOCKET sock = copy.fd_array[i];

			/* Is it an inbound communication? */
			if (sock == listening)
			{
				/* Accept a new connection */
				SOCKET client = accept(listening, nullptr, nullptr);

				/* Add the new connection to the list of connected clients */
				FD_SET(client, &master);

				/* Send a welcome message to the connected client */
				string welcomeMsg = "Welcome to connected to Server!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

			}
			/* It's an inbound message */
			else
			{
				string ByteReceived;
				string Data[5];

				/* Received data from client */
				int bytesIn = Received(&sock,&ByteReceived);
				
				/* Split data received from client */
				this->SplitData(ByteReceived, Data, '_');

				if (bytesIn <= 0)
				{
					/* Drop the client */
					this->QuitGame(&sock);
				}
				else
				{
					/* Check to see if it's a command. \quit kills the server */
					if (ByteReceived[0] == '\\')
					{
						if (Data[0] == "\\quit")
						{
							running = false;
							break;
						}

						// Unknown command
						continue;
					}

					if (Data[0] == "START")
					{
						this->StartGame(&sock);
					}
					else if (Data[0] == "END")
					{
						this->EndGame(&sock);
					}
					else if (Data[0] == "LOGIN")
					{
						this->LogInClient(&sock, Data);
					}
					else if (Data[0] == "SIGN UP")
					{
						this->SignUpClient(&sock, Data);
					}
					else if (Data[0] == "SAVE")
					{
						this->SaveClient(&sock, Data);
					}
					else
					{
						this->TranferClient(&sock,i,Data);
					}
				}
			}
		}
	}
}


void multiclient::RemoveListening()
{
	/* Remove the listening socket from the master file descriptor setand close it
	   to prevent anyone else trying to connect.
	*/
	FD_CLR(listening, &master);
	closesocket(listening);

}


void multiclient::MessageHappen()
{
	/* Message to let users know what's happening */
	string msg = "Server is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)
	{
		/* Get the socket number */
		SOCKET sock = master.fd_array[0];

		/* Send the goodbye message */
		send(sock, msg.c_str(), msg.size() + 1, 0);

		/* Remove it from the master file list and close the socket */
		FD_CLR(sock, &master);
		closesocket(sock);
	}
}


void multiclient::CleanupWinsock()
{
	/* Cleanup winsock */
	WSACleanup();
}


int multiclient::Send(SOCKET *sock, string Data)
{
	int sendResult = 0;

	sendResult = send(*sock, Data.c_str(), Data.size() + 1, 0);

	return sendResult;
}


int multiclient::Received(SOCKET* sock, string* Str)
{
	char buf[4096];
	ZeroMemory(buf, 4096);
	int bytesReceived;

	bytesReceived = recv(*sock, buf, 4096, 0);

	(*Str) = string(buf, 0, bytesReceived);

	return bytesReceived;
}


void multiclient::StartGame(SOCKET* sock)
{
	string DataSend;

	if (this->Flag == 0)
	{
		for (int i = 0; i < master.fd_count; i++)
		{
			DataSend = "BEFORE_" + to_string(i);
			SOCKET outSock = master.fd_array[i];

			if (outSock != listening && outSock == *sock)
			{
				/* Send data to client */
				this->Send(&outSock, DataSend);

				/* Save ID of sock into arrange: Player1 */
				unsigned char j = 1;
				while ((Arrange[j += 2] != 0) && (j<20));

				Arrange[j] = outSock;
				IndexArrange = j;
			}
		}
		/* Wait to next client */
		this->Flag = 1;
	}
	else
	{
		for (int i = 0; i < master.fd_count; i++)
		{
			SOCKET outSock = master.fd_array[i];
			if (outSock != listening && outSock == (*sock))
			{
				/* Save ID of sock into arrange: Player2 */
				Arrange[IndexArrange + 1] = outSock;

				SOCKET outSock1 = Arrange[IndexArrange];
				SOCKET outSock2 = Arrange[IndexArrange+1];

				/* Send data to client1 */
				DataSend = "AFTER_";
				this->Send(&outSock1, DataSend);

				/* Send data to client1 */
				DataSend = "AFTER_";
				this->Send(&outSock2, DataSend);

				/* Reset Flag to use for next couple */
				this->Flag = 0;
			}
		}
	}
}


void multiclient::EndGame(SOCKET* sock)
{
	for (int i = 0; i < master.fd_count; i++)
	{
		SOCKET outSock = master.fd_array[i];

		if (outSock != listening && outSock == (*sock))
		{
			unsigned char j = 1;

			/* Delete Client in Array arrange match */
			while (j<20)
			{
				if (outSock == Arrange[j])
				{
					Arrange[j] = 0;
				}
				j++;
			}
		}
	}
}


void multiclient::QuitGame(SOCKET* sock)
{

	for (int i = 0; i < master.fd_count; i++)
	{
		SOCKET outSock = master.fd_array[i];
		if (outSock != listening && outSock == (*sock))
		{
			unsigned char j = 1;

			while (j<20)
			{
				if (outSock == Arrange[j])
				{
					if ((j % 2) != 0)
					{
						/* Send Signal "OUT GAME" to competition */
						SOCKET outSock = Arrange[j + 1];
						string DataSend = "OUT GAME";
						this->Send(&outSock, DataSend);

						/* Delete Client in Array arrange match */
						Arrange[j] = 0;
						Arrange[j + 1] = 0;
					}
					else
					{
						/* Send Signal "OUT GAME" to competition */
						SOCKET outSock = Arrange[j - 1];
						string DataSend = "OUT GAME";
						this->Send(&outSock, DataSend);

						/* Delete Client in Array arrange match */
						Arrange[j] = 0;
						Arrange[j - 1] = 0;
					}
					break;
				}
				j++;
			}
		}
	}
	closesocket(*sock);
	FD_CLR(*sock, &master);
}


void multiclient::LogInClient(SOCKET *sock, string Data[])
{
	sqlserver SQL;
	int Result = 0;
	int Win = 0;
	int Lose = 0;
	Data_t Database;

	Database.Name = Data[1];

	/* Check Username and password into database */
	Result = SQL.LogIn(Data[1], Data[2]);

	/* Get information of player from database */
	if (Result == 1)
	{
		SQL.GetDataPlayer(&Database);
	}


	for (int i = 0; i < master.fd_count; i++)
	{
		SOCKET outSock = master.fd_array[i];
		if (outSock != listening && outSock == (*sock))
		{
			/* Send information of player to client */
			string DataSend = to_string(Result) + "_" + to_string(Database.Win) + "_" 
				            + to_string(Database.Lose)+ "_" + to_string(Database.Equal);
			this->Send(&outSock, DataSend);
		}
	}
}


void multiclient::SignUpClient(SOCKET *sock, string Data[])
{
	sqlserver SQL;
	int Result = 0;

	/* Check account into database */
	Result = SQL.LogIn(Data[1], Data[2]);

	/* Write account to database */
	if (Result == 2)
	{

		Result = SQL.SignUp(Data[1], Data[2]);

		/* Send respond to client */
		for (int i = 0; i < master.fd_count; i++)
		{
			SOCKET outSock = master.fd_array[i];
			if (outSock != listening && outSock == (*sock))
			{
				string DataSend = "OK_";
				this->Send(&outSock, DataSend);
			}
		}
	}
	else
	{ 
		/* Send respond to client */
		for (int i = 0; i < master.fd_count; i++)
		{
			SOCKET outSock = master.fd_array[i];
			if (outSock != listening && outSock == (*sock))
			{
				string DataSend = "FAIL_" + to_string(Result);
				this->Send(&outSock, DataSend);
			}
		}
	}
}


void multiclient::SaveClient(SOCKET *sock, string Data[])
{
	sqlserver SQL;
	int Result = 0;
	int Win = 0;
	int Lose = 0;
	Data_t Database;

	Database.Name = Data[1];
	Database.Win =  stoi(Data[2]);
	Database.Lose = stoi(Data[3]);
	Database.Equal = stoi(Data[4]);

	/* Write information of player to database */
	SQL.SetDataPlayer(&Database);

	/* Send respond to client */
	string DataSend = "SAVE OK_" + to_string(Result);
	this->Send(sock, DataSend);
}


void multiclient::TranferClient(SOCKET *sock, int i, string Data[])
{

	for (int i = 0; i < master.fd_count; i++)
	{
		SOCKET outSock = master.fd_array[i];
		if (outSock != listening && outSock == (*sock))
		{
			unsigned char j = 1;
			while (j<20)
			{
				if (Arrange[j] == outSock)
				{
					if ((j % 2) != 0)
					{
						/* Send data to other client in couple */
						SOCKET outSock = Arrange[j + 1];
						string DataSend = Data[0] + "_" + Data[1] + "_" + Data[2];
						this->Send(&outSock, DataSend);
					}
					else
					{
						/* Send data to other client in couple */
						SOCKET outSock = Arrange[j - 1];
						string DataSend = Data[0] + "_" + Data[1] + "_" + Data[2];
						this->Send(&outSock, DataSend);
					}
					break;
				}
				j++;
			}
		}
	}
}


void multiclient::SplitData(std::string StrIn, std::string *StrOut, char Character)
{
	int i = 0;
	int j = 0;

	while (NULL !=StrIn[i])
	{
		if (Character != StrIn[i])
		{
			StrOut[j] += StrIn[i];
		}
		else
		{
			j++;
		}
		i++;
	}
}