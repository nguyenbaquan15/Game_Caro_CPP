#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>

#include "chesstable.h"
#include "player.h"
#include "play.h"
#include "connectserver.h"
#include "replay.h"
#include "checkwin.h"

using namespace std;


void play::PlayOffline(player *Player1, player *Player2)
{
	bool finish = false;
	bool Status = 0;
	chesstable ChessTable(10, 10);
	int PosX;
	int PosY;

	replay Replay;
	string DataWrite;
	clock_t start;
	clock_t end;
	double time;

	/* Initialize a chess table */
	ChessTable.Init();
	ChessTable.Display();

	/* Open file to replay match */
	Replay.OpenWrite();


	while (finish != true)
	{
		system("cls");
		ChessTable.Display();

		if (0 == Status)
		{
			cout << "Player 1 turn:";

			/* Begin count time to replay match */
			start = clock();

			this->EnterPosition(&ChessTable, &PosX, &PosY);
			Player1->SetPosX(PosX);
			Player1->SetPosY(PosY);
			ChessTable.SetPos(PosX, PosY,'x');
			ChessTable.SetCount();

			/* End count time to replay match */
			end = clock();

			time = (double(end) - double(start)) / CLOCKS_PER_SEC;

			/* Write data into file */
			DataWrite = "x_" + to_string(Player1->GetPosX()) + "_"
				+ to_string(Player1->GetPosY()) + "_" + to_string(time);

			Replay.Write(DataWrite);

			checkwin::Win(ChessTable,Player1);

			if (1 == checkwin::GetResult())
			{
				system("cls");
				ChessTable.Display();
				cout << "Player 1 win" << endl;
				Player1->SetWin();
				Player2->SetLose();
				Replay.Write("1");
				finish = true;
			}
			checkwin::ResetResult();
			Status = 1;
		}
		else
		{
			cout << "Player 2 turn:";

			/* Begin count time to replay match */
			start = clock();

			this->EnterPosition(&ChessTable, &PosX, &PosY);
			Player2->SetPosX(PosX);
			Player2->SetPosY(PosY);
			ChessTable.SetPos(PosX, PosY, 'o');
			ChessTable.SetCount();

			/* End count time to replay match */
			end = clock();

			time = (double(end) - double(start)) / CLOCKS_PER_SEC;

			/* Write data into file */
			DataWrite = "o_" + to_string(Player2->GetPosX()) + "_"
				+ to_string(Player2->GetPosY()) + "_" + to_string(time);

			Replay.Write(DataWrite);
			checkwin::Win(ChessTable,Player2);

			if (1 == checkwin::GetResult())
			{
				system("cls");
				ChessTable.Display();
				cout << "Player 2 win" << endl;
				Player2->SetWin();
				Player1->SetLose();
				Replay.Write("2");
				finish = true;
			}
			checkwin::ResetResult();
			Status = 0;
		}

		/* Check Equal */
		if (1 == ChessTable.isFullTable())
		{
			system("cls");
			ChessTable.Display();
			cout << "2 Player are equal" << endl;
			Player1->SetEqual();
			Player2->SetEqual();
			Replay.Write("3");
			finish = true;
		}
	}
	Replay.Close();

}


void play::PlayOnline(connectSever* Client, player* Player)
{
	int PosX=0;
	int PosY=0;
	chesstable ChessTable(10, 10);
	bool finish = false;
	string choseClient;
	string DataSend;

	replay Replay;
	string DataWrite;
	clock_t start;
	clock_t end;
	double time;

	/* Send signal "START" to Server */
	choseClient = Client->Start();

	/* Open file to replay match */
	Replay.OpenWrite();

	/*---------------------------- Program for client1 --------------------------------*/
	if (choseClient == "BEFORE")
	{
		while (finish == false)
		{
			/*................................Send Data................................*/
			system("cls");
			ChessTable.Display();
			Player->SetCharacter('x');
			cout << "Player 1 turn:";

			/* Begin count time to replay match */
			start = clock();
			this->EnterPosition(&ChessTable, &PosX, &PosY);
			Player->SetPosX(PosX);
			Player->SetPosY(PosY);
			ChessTable.SetPos(PosX,PosY, Player->GetCharacter());
			ChessTable.SetCount();

			/* End count time to replay match */
			end = clock();
			time = (double(end) - double(start)) / CLOCKS_PER_SEC;

			/* Write data into file */
			DataWrite = "x_" + to_string(Player->GetPosX()) + "_"
				+ to_string(Player->GetPosY()) + "_" + to_string(time);

			Replay.Write(DataWrite);

			int result = 0;
			/* Check win - lose */
			checkwin::Win(ChessTable, Player);
			result = checkwin::GetResult();
			checkwin::ResetResult();

			if (1 == result)
			{
				/* Format of data */
				DataSend = "WIN_" + to_string(PosX) + "_" + to_string(PosY);

				/* Send data to server */
				Client->Send(DataSend);

				system("cls");
				ChessTable.Display();
				cout << "Player 1 win" << endl;
				Player->SetWin();
				Replay.Write("1");
				finish = true;
			}
			else if (0 == result)
			{
				/* Format of data */
				DataSend = "EQUAL_" + to_string(PosX) + "_" + to_string(PosY);

				/* Send data to server */
				Client->Send(DataSend);

				system("cls");
				ChessTable.Display();
				cout << "2 Player Equal" << endl;
				Player->SetEqual();
				Replay.Write("3");
				finish = true;
			}
			else
			{
				/* Format of data */
				DataSend = "PLAY_" + to_string(PosX) + "_" + to_string(PosY);

				/* Send data to server */
				Client->Send(DataSend);
			}
			/*..............................Send Data.................................*/


			/*...........................Received Data................................*/
			if (finish == false)
			{
				system("cls");
				ChessTable.Display();

				string DataReceived;
				string DataSplit[5];

				/* Begin count time to replay match */
				start = clock();

				/* Wait received data from server */
				DataReceived = Client->Received();

				/* Split data received from server */
				Client->SplitData(DataReceived, DataSplit, '_');

				/* End count time to replay match */
				end = clock();
				time = (double(end) - double(start)) / CLOCKS_PER_SEC;

				/* Write data into file */
				DataWrite = "o_" + DataSplit[1] + "_" + DataSplit[2] + "_" + to_string(time);

				Replay.Write(DataWrite);

				if (DataSplit[0] == "PLAY")
				{
					/* Set coordinate for table and player */
					ChessTable.SetPos(stoi(DataSplit[1]), stoi(DataSplit[2]), 'o');
					ChessTable.SetCount();
				}
				else if (DataSplit[0] == "WIN")
				{
					ChessTable.SetPos(stoi(DataSplit[1]), stoi(DataSplit[2]), 'o');
					system("cls");
					ChessTable.Display();
					cout << "Player 2 win" << endl;
					Player->SetLose();
					Replay.Write("2");
					finish = true;
				}
				else if (DataSplit[0] == "EQUAL")
				{
					ChessTable.SetPos(stoi(DataSplit[1]), stoi(DataSplit[2]), 'o');
					system("cls");
					ChessTable.Display();
					cout << " 2 player Equal" << endl;
					Player->SetEqual();
					Replay.Write("3");
					finish = true;
				}

				else if (DataSplit[0] == "OUT GAME")
				{
					cout << "Competitor Out game!" << endl;
					finish = true;
				}
			/*.............................Received Data................................*/
			}
		}
	}
	/*---------------------------- Program for client1 --------------------------------*/


	/*---------------------------- Program for client2 --------------------------------*/
	else if (choseClient == "AFTER")
	{
		while (finish == false)
		{

			/*.............................Received Data................................*/
			system("cls");
			ChessTable.Display();

			Player->SetCharacter('o');

			/* Begin count time to replay match */
			start = clock();

			string DataReceived;
			string DataSplit[5];

			/* Wait received data from server */
			DataReceived = Client->Received();

			/* Split data received from server */
			Client->SplitData(DataReceived, DataSplit, '_');

			/* End count time to replay match */
			end = clock();
			time = (double(end) - double(start)) / CLOCKS_PER_SEC;

			/* Write data into file */
			DataWrite = "x_" + DataSplit[1] + "_" + DataSplit[2] + "_" + to_string(time);

			Replay.Write(DataWrite);

			if (DataSplit[0] == "PLAY")
			{
				/* Set coordinate for table and player */
				ChessTable.SetPos(stoi(DataSplit[1]), stoi(DataSplit[2]), 'x');
				ChessTable.SetCount();
			}
			else if (DataSplit[0] == "WIN")
			{
				ChessTable.SetPos(stoi(DataSplit[1]), stoi(DataSplit[2]), 'x');
				system("cls");
				ChessTable.Display();
				Player->SetLose();
				cout << "Player 1 win" << endl;
				Player->SetLose();
				Replay.Write("1");
				finish = true;
				continue;
			}
			else if (DataSplit[0] == "EQUAL")
			{
				ChessTable.SetPos(stoi(DataSplit[1]), stoi(DataSplit[2]), 'x');
				system("cls");
				ChessTable.Display();
				cout << " 2 player Equal" << endl;
				Player->SetEqual();
				Replay.Write("3");
				finish = true;
			}
			else if (DataSplit[0] == "OUT GAME")
			{
				cout << "Competitor Out game!" << endl;
				finish = true;
				continue;
			}
			system("cls");
			ChessTable.Display();
			/*............................Received Data...............................*/


			/*................................Send Data..............................*/
			cout << "Player 2 turn:";

			/* Begin count time to replay match */
			start = clock();
			this->EnterPosition(&ChessTable,&PosX,&PosY);

			Player->SetPosX(PosX);
			Player->SetPosY(PosY);
			ChessTable.SetPos(PosX,PosY, Player->GetCharacter());
			ChessTable.SetCount();

			/* End count time to replay match */
			end = clock();
			time = (double(end) - double(start)) / CLOCKS_PER_SEC;

			/* Write data into file */
			DataWrite = "o_" + to_string(Player->GetPosX()) + "_"
				+ to_string(Player->GetPosY()) + "_" + to_string(time);

			Replay.Write(DataWrite);

			int result;
			/* Check win - lose */
			checkwin::Win(ChessTable, Player);
			result = checkwin::GetResult();
			checkwin::ResetResult();

			if (1 == result)
			{
				/* Format of data */
				DataSend = "WIN_" + to_string(PosX) + "_" + to_string(PosY);

				/* Send data to server */
				Client->Send(DataSend);

				system("cls");
				ChessTable.Display();
				cout << "Player 2 win" << endl;
				Player->SetWin();
				Replay.Write("2");
				finish = true;
			}
			else if (0 == result)
			{
				/* Format of data */
				DataSend = "EQUAL_" + to_string(PosX) + "_" + to_string(PosY);

				/* Send data to server */
				Client->Send(DataSend);

				system("cls");
				ChessTable.Display();
				cout << "2 Player Equal" << endl;
				Player->SetEqual();
				Replay.Write("3");
				finish = true;
			}
			else
			{
				/* Format of data */
				DataSend = "PLAY_" + to_string(PosX) + "_" + to_string(PosY);

				/* Send data to server */
				Client->Send(DataSend);
			}

			/*..............................Send Data..................................*/
		}
	}
	/*---------------------------- Program for client2 --------------------------------*/

	Replay.Close();
}


void play::EnterPosition(chesstable* Table, int* PosX, int* PosY)
{
	bool loop1 = 1;
	bool loop2 = 1;

	do
	{
		/* Enter coordinate of player */
		cin >> (*PosX) >> (*PosY);

		if (cin.fail()) {
			cout << "Wrong input. Please enter one integer\n";
			std::cin.clear();
			//std::cin.ignore(256, '\n');   // ignore the line change
			cin.ignore();
		}
		else
		{
			loop1 = 0;
		}

		if ((loop1 == 0) && (Table->GetValuePosXY(*PosX, *PosY) == 0))
		{
			loop2 = 0;
		}
		else
		{
			loop1= 1;
			cout << "Exist!";
			cout << "Enter other position:";
		}
	} while (loop1 || loop2);

}
