/**********************************************************/
/*
/* Socket library
/* Function: connect client with server through Socket TCP/IP
/*
/**********************************************************/
#pragma once

#include <WS2tcpip.h>
#include "player.h"

#pragma comment(lib, "ws2_32.lib")


class connectSever
{
	private:
		SOCKET sock;

		// IP Address of the server
		std::string ipAddress;

		// Listening port on the server
		int port;

	public:
		/* IP address and Port default */
		connectSever();

		/* IP address and Port setup */
		connectSever(std::string ipAddress, int port);

		/* Initialize a Socket */
		int Init();

		/* Send signal "START" to Server for arrange match */
		string Start();

		/* Send data to Server */
		int Send(string Data);

		/* Received data from Server */
		string Received();

		/* Send information of player to Server */
		int SendPlayer(player* Player);

		/* Split data received from Server */
		void SplitData(std::string StrIn, std::string* StrOut, char Character);

		/* Disconnect a Socket */
		void Disconnect();

};