#include <iostream>
#include <conio.h>
#include <unordered_set>
#include <iomanip>
#include <string>
#include <fstream>
#include <TCHAR.h>
#include "chesstable.h"
#include "player.h"
#include "play.h"
#include "menuview.h"
#include "control.h"
#include "fileconfig.h"
#include "replay.h"
#include "console.h"
#include <windows.h>
#include <time.h>


using namespace std;


controll::controll(string ipAddress, int port)
{
	this->Client = new connectSever(ipAddress, port);
}


controll::~controll()
{
	delete (this->Client);
	(this->Client) = nullptr;
}


void controll::chosemenu()
{
	bool LoopMode = 1;

	while (LoopMode)
	{
		int choseMode;
		system("cls");
		menuview::ChoseMenu(choseMode);

		switch (choseMode)
		{
			/* Program controll Play Online */
			case 1:
			{
				/* Initialize Socket */
				if (0 == Client->Init())
				{
					cout << "Check connect Internet!" << endl;
					cout << "Please enter 1 character to continue:" << endl;
					_getch();
					continue;
				}

				player Player;
				bool loopOnLine = 1;

				/* Chose function when Play online */
				while (loopOnLine)
				{
					int choseOnline;
					bool exit = 0;
					system("cls");
					menuview::MenuPlayOnline(choseOnline);

					switch (choseOnline)
					{
						case 1:
						{
							controll::LoginOnline(&Player);
							break;
						}
						case 2:
						{
							controll::SignupOnline();
							break;
						}
						case 3:
						{
							controll::PlayOnline(&Player);
							break;
						}
						case 4:
						{
							controll::ShowInfo(&Player);
							break;
						}
						case 5:
						{
							controll::Replay();
							break;
						}
						case 0:
						{
							loopOnLine = 0;
							exit = 1;
							continue;
						}
						default:
						{
							/* do nothing */
						}
					}
					if (exit == 0)
					{
						cout << "Enter 1 character to continue:";
						_getch();
					}
				}
				Client->Disconnect();
				break;
			}

			/* Program controll Play Offline */
			case 2:
			{
				bool loopOffline = 1;
				player Player[2];

				/* Chose function when Play online */
				while(loopOffline)
				{
					bool exit = 0;
					int choseOffline;
					system("cls");
					menuview::MenuPlayOffline(choseOffline);

					switch (choseOffline)
					{
						case 1:
						{
							controll::LoginOffline(&Player[0]);
							break;
						}
						case 2:
						{
							controll::SignupOffline();
							break;
						}
						case 3:
						{
							controll::PlayOffline(&Player[0]);
							break;
						}
						case 4:
						{
							controll::ShowInfo(&Player[0]);
							controll::ShowInfo(&Player[1]);
							break;
						}
						case 5:
						{
							controll::Replay();
							break;
						}
						case 0:
						{
							loopOffline = 0;
							continue;
						}
						default:
						{
							/* do nothing */
						}
					}
					if (exit == 0)
					{
						cout << "Enter 1 character to continue:";
						_getch();
					}
				}
				break;

			}
			case 0:
			{
				LoopMode = 0;
				continue;
			}
			default:
			{
				/* do nothing */
			}
		}
	}
}


void controll::LoginOnline(player *Player)
{
	string UserName;
	string PassWord;
	string DataSend;
	string DataReceived;
	string DataSplit[5];
	infoplayer_t Info;


	console::gotoXY(40, 29);
	cout << "User Name:";
	getline(cin, UserName);
	console::gotoXY(40, 30); 
	cout << "PassWord:";

	/* Enter and Hide password on console */
	char ch;
	ch = _getch();
	while (ch != 13)
	{	
		//character 13 is enter
		PassWord.push_back(ch);
		cout << '*';
		ch = _getch();
	}

	/* Format of data */
	DataSend = "LOGIN_"+ UserName + "_" + PassWord;

	/* Send data to server */
	Client->Send(DataSend);

	/* Wait received data from server */
	DataReceived=Client->Received();

	/* Split data received from server */
	Client->SplitData(DataReceived, DataSplit, '_');

	if ("1" == DataSplit[0])
	{
		console::gotoXY(40, 31);
		cout << "Log in success!" << endl;

		/* Load data of player */
		Info.Name = UserName;
		Info.Win =  std::stoi(DataSplit[1]);
		Info.Lose = std::stoi(DataSplit[2]);
		Info.Equal = std::stoi(DataSplit[3]);
		Player->SetInfo(Info);

	}
	else if ("0" == DataSplit[0])
	{
		console::gotoXY(40, 31);
		cout << "Password wrong! Please enter password again" << endl;
	}
	else
	{
		console::gotoXY(40, 31);
		cout << "User not exist. Please sign up" << endl;
	}

}


void controll::SignupOnline()
{
	string UserName;
	string PassWord;
	string DataSend;
	string DataReceived;
	string DataSplit[5];

	console::gotoXY(40, 27);
	cout << "Sign up" << endl;
	console::gotoXY(40, 28);
	cout << "User Name:";
	getline(cin, UserName);
	console::gotoXY(40, 29);
	cout << "PassWord:";

	/* Enter and Hide password on console */
	char ch;
	ch = _getch();
	while (ch != 13)
	{
		//character 13 is enter
		PassWord.push_back(ch);
		cout << '*';
		ch = _getch();
	}

	/* Format of data */
	DataSend = "SIGN UP_" + UserName + "_" + PassWord;

	/* Send Data to server */
	Client->Send(DataSend);

	/* Wait received data from server */
	DataReceived = Client->Received();

	/* Split data received from server */
	Client->SplitData(DataReceived, DataSplit, '_');

	if ("OK" == DataSplit[0])
	{
		console::gotoXY(40, 31);
		cout << "Sign up success!" << endl;
	}
	else if (("1" == DataSplit[1])||("0" == DataSplit[1]))
	{
		console::gotoXY(40, 31);
		cout << "Account exist in system!" << endl;
	}
	else
	{
		console::gotoXY(40, 31);
		cout << "Sign up fail" << endl;
	}

}


void controll::PlayOnline(player *Player)
{
	play Play;
	infoplayer_t Info;

	Info = Player->GetInfo();

	/* Unless Login, you can't Play */
	if ("Default" == Info.Name)
	{
		cout << "You haven't login! Please Login!" << endl;
		return;
	}

	/* Connect to server and Play game */
	Play.PlayOnline(Client, Player);

	/* Write Result to database */
	Client->SendPlayer(Player);

	string DataReceived;
	string DataSplit[5];
	DataReceived = Client->Received();
	Client->SplitData(DataReceived, DataSplit, '_');

	/* Send signal end game to server */
	if ("SAVE OK" == DataSplit[0])
	{
		Client->Send("END");
	}
}


void controll::LoginOffline(player* Player)
{
	string UserName;
	string PassWord;
	fileconfig File;
	int Position;
	int Result=0;
	int x=0;

	/* Login with 2 player */
	for (int i = 0; i < 2; i++)
	{
		console::gotoXY(40, 27+i+x);
		cout << "UserName Player "<<i+1<<" :";
		getline(cin, UserName);
		console::gotoXY(40, 28+i+x);
		cout << "PassWord:";

		/* Enter and Hide password on console */
		char ch;
		ch = _getch();
		while (ch != 13)
		{
			//character 13 is enter
			PassWord.push_back(ch);
			cout << '*';
			ch = _getch();
		}

		/* Check account in File.ini */
		Result = File.LogIn(UserName, PassWord, &Position);

		if (1 == Result)
		{
			console::gotoXY(40, 29 + i+x);
			cout << "Login success!" << endl;
			File.ReadPlayer(Position, Player+i);
		}
		else if (0 == Result)
		{
			console::gotoXY(40, 29 + i+x);
			cout << "PassWord Wrong! Please enter again!" << endl;
		}
		else
		{
			console::gotoXY(40, 29 + i+x);
			cout << "User not exist. Please sign up" << endl;
		}

		/* Increase index to display on console next */
		x += 3;

		/* Reset variable */
		UserName = "";
		PassWord = "";
	}
}


void controll::SignupOffline()
{
	string UserName;
	string PassWord;
	fileconfig File;
	int Result;

	console::gotoXY(40, 27);
	cout << "User Name:";
	getline(cin, UserName);
	console::gotoXY(40, 28);
	cout << "PassWord:";

	/* Enter and Hide password on console */
	char ch;
	ch = _getch();
	while (ch != 13)
	{
		//character 13 is enter
		PassWord.push_back(ch);
		cout << '*';
		ch = _getch();
	}

	/* Check Account in file.ini */
	Result = File.SignUp(UserName, PassWord);

	if (3 == Result)
	{
		cout << "Sign up success!" << endl;
	}
	else if ((0 ==Result) || (1 == Result))
	{
		cout << "Account exist in system!" << endl;
	}
	else
	{
		cout << "Sign up fail" << endl;
	}

}


void controll::PlayOffline(player *Player)
{
	play Play;
	fileconfig File;
	infoplayer_t Info;


	Info = Player->GetInfo();

	/* Unless Login, you can't Play */
	if ("Default" == Info.Name)
	{
		cout << "You haven't login! Please Login!" << endl;
		return;
	}

	Play.PlayOffline(Player, Player+1);

	/* Save information of player */
	File.WritePlayer(Player);
	File.WritePlayer(Player+1);

}


 void controll::ShowInfo(player *Player)
{
	 infoplayer_t Info;

	 Info = Player->GetInfo();

	 /* Unless Login, you can't see information of player */
	 if ("Default" == Info.Name)
	 {
		 cout << "You haven't login! Please Login!" << endl;
		 return;
	 }

	 cout << "Information of player:" << endl;
	 Player->DisplayPlayer();

}


void controll::Replay()
{
	replay Replay;
	chesstable Table(10,10);

	/* Open file replay.txt */
	Replay.OpenRead();

	while (!Replay.isEndFile())
	{
		string Data;
		string DataSplit[4];

		/* Read file */
		Replay.Read(&Data);

		/* Split data */
		Replay.SplitData(Data, DataSplit,'_');

		/* Enter information of match on chess table */
		/*------------------------------------------------------------------------------*/
		if (DataSplit[0] == "x")
		{
			Table.SetPos(std::stoi(DataSplit[1]), std::stoi(DataSplit[2]), 'x');
			system("cls");
			Table.Display();
			Sleep(std::stod(DataSplit[3])*1000);
		}
		else if (DataSplit[0] == "o")
		{
			Table.SetPos(std::stoi(DataSplit[1]), std::stoi(DataSplit[2]), 'o');
			system("cls");
			Table.Display();
			Sleep(std::stod(DataSplit[3])*1000);
		}
		else if(DataSplit[0]=="1")
		{
			cout << "Player 1 win"<<endl;
		}
		else if(DataSplit[0] == "2")
		{
			cout << "Player 2 win"<<endl;
		}
		else if (DataSplit[0] == "3")
		{
			cout << "2 Player is equal2" << endl;
		}
		/*------------------------------------------------------------------------------*/
	}

	Replay.Close();
	
}