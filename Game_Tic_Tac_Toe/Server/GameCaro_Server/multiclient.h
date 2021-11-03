#pragma once

#include <iostream>
#include <WS2tcpip.h>

class multiclient
{
	private:

		/* Create a socket */
		SOCKET listening;

		/* Create the master file descriptor set and zero it */
		fd_set master;
		int PORT;

		/* Flag variable use to connect 2 client each other */
		bool Flag=0;

		/* Create a array to save couple in match, arrange match */
		unsigned int Arrange[20] = {0};
		unsigned char IndexArrange = 0;

	public:

		multiclient(int Port);

		/* Initialize winsock */
		void Init();

		/* Create a socket */
		void CreateSocket();

		/* Assign port */
		void BindIpAddr();

		/* Create the master file descriptor set */
		void CreateMaster();

		/* Wait connect from client */
		void Listening();

		/* Remove the listening socket from the master file descriptor */
		void RemoveListening();

		/* Message to let users know what's happening */
		void MessageHappen();

		/* Cleanup winsock */
		void CleanupWinsock();

		/* Send data to a client */
		int Send(SOCKET *sock, std::string Data);

		/* Received data from a client */
		int Received(SOCKET *sock, std::string* Str);

		/* Handle when received command "START" from client */
		void StartGame(SOCKET *sock);

		/* Handle when received command "END" from client */
		void EndGame(SOCKET* sock);

		/* Handle when received command "END" from client */
		void QuitGame(SOCKET* sock);
	
		/* Handle when received command "LOGIN" from client   */
		void LogInClient(SOCKET *sock, std::string Data[]);

		/* Handle when received command "SIGN UP" from client   */
		void SignUpClient(SOCKET *sock, std::string Data[]);

		/* Handle when received command "SAVE" from client   */
		void SaveClient(SOCKET *sock, std::string Data[]);

		/* Handle when received command "PLAY" from client   */
		void TranferClient(SOCKET *sock, int i, std::string Data[]);

		/* Split data received from client */
		void SplitData(std::string StrIn, std::string *StrOut, char Character);

};