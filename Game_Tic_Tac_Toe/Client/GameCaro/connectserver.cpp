#include <iostream>
#include <cstdlib>

#include <string>
#include <sstream>
#include <typeinfo>

#include "connectserver.h"
#include "console.h"

using namespace std;


connectSever::connectSever()
{
	this->ipAddress = "127.0.0.1";
	this->port = 54000;
}


connectSever::connectSever(string ipAddress, int port)
{
	this->ipAddress = ipAddress;
	this->port = port;
}


int connectSever::Init()
{
	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);

	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	string DataReceived;
	string DataSplit[5];

	/* Wait received data from server */
	DataReceived = this->Received();

	/* Split data received from server */
	this->SplitData(DataReceived, DataSplit, '_');

	if (DataSplit[0]!="")
	{
		// Echo response to console
		console::gotoXY(40, 28);
		cout << "SERVER> " << DataReceived << endl;
		return 1;
	}
}


string connectSever::Start()
{
	string chose;
	string DataReceived;
	string DataSplit[5];
	string DataSend;

	do
	{
		/* Format of data */
		DataSend = "START";

		/* Send data to server */
		this->Send(DataSend);

		/* Wait received data from server */
		DataReceived = this->Received();

		/* Split data received from server */
		this->SplitData(DataReceived, DataSplit, '_');

	} while (0);


	if ("BEFORE" == DataSplit[0])
	{
		cout << "Wait other client connect!";

		/* Wait received data from server */
		DataReceived = this->Received();
	}
	else if("AFTER" == DataSplit[0])
	{
		/* do nothing */
	}

	/* Purpose of chose variable: See client send data before, client received data */
	chose = DataSplit[0];

	return chose;

}


int connectSever::Send(string Data)
{
	int sendResult;
	sendResult = send(sock, Data.c_str(), Data.size() + 1, 0);

	return sendResult;
}


string connectSever::Received()
{
	char buf[4096];
	ZeroMemory(buf, 4096);
	int bytesReceived;

	bytesReceived = recv(sock, buf, 4096, 0);

	string Received = string(buf, 0, bytesReceived);

	return Received;
}


int connectSever::SendPlayer(player *Player)
{
	int sendResult=0;
	string DataSend;
	infoplayer_t Info;

	Info = Player->GetInfo();

	DataSend = "SAVE_" + Info.Name + "_" + to_string(Info.Win) + "_" + to_string(Info.Lose)+ "_"+ to_string(Info.Equal);

	this->Send(DataSend);

	return sendResult;
}


void connectSever::Disconnect()
{
	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();

}


void connectSever::SplitData(std::string StrIn, std::string* StrOut, char Character)
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