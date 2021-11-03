/**********************************************************/
/*
/* Function: Control main program
/*
/**********************************************************/
#pragma once

#include "player.h"
#include "connectserver.h"

class controll
{
	private:
		/* Create a connect to Server */
		connectSever* Client;

	public:

		controll(string ipAddress, int port);
		~controll(); 

		/* Chose function of menu */
		void chosemenu();

		/* Program handle Login to Server */
		void LoginOnline(player *Player);

		/* Program handle Sign up to Server */
		void SignupOnline();

		/* Program Play with network */
		void PlayOnline(player *Player);

		/* Program handle Login into File.ini */
		void LoginOffline(player* Player);

		/* Program handle Sign up into File.ini  */
		void SignupOffline();

		/* Program handle Play without network */
		void PlayOffline(player *Player);

		/* Program display information of player */
		void ShowInfo(player *Player);

		/* Program handle Replay match */
		void Replay();

		void Exit();

};