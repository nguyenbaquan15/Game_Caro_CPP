#include <iostream>
#include "menuview.h"
#include "console.h"

using namespace std;


void menuview::ChoseMenu(int &chose)
{
    bool loop=0;
	
	do
	{
		system("cls");
		PrintCaro();
		cout<<"\n";

		console::gotoXY(40, 17); cout << "********************************************" << endl;
		console::gotoXY(40, 18); cout << "*                 GAME CARO                *" << endl;
		console::gotoXY(40, 19); cout << "*                  1.Play ONLINE           *" << endl;
		console::gotoXY(40, 20); cout << "*                  2.Play OFFLINE          *" << endl;
		console::gotoXY(40, 21); cout << "*                  0.Exit                  *" << endl;
		console::gotoXY(40, 22); cout << "********************************************" << endl;
    
		console::gotoXY(40, 24); cout << "Please choice:";
		cin >> chose;
		if (cin.fail())
		{
			console::gotoXY(40, 25);
			cout << "Please enter again";
			std::cin.clear();
			cin.ignore();
			loop = 1;
		}
		else if ((chose < 0) || (chose > 2))
		{
			loop = 1;
		}
		else
		{
			loop = 0;
		}
		cin.ignore();

    } while (loop);

}


void menuview::MenuPlayOnline(int& chose)
{
	bool loop = 0;

	do
	{
		system("cls");
		PrintCaro();
		cout << "\n";

		console::gotoXY(40, 17); cout << "********************************************" << endl; console::Textcolor(BC_Green);
		console::gotoXY(40, 18); cout << "*     -----ONLINE------------ONLINE-----   *" << endl; console::Textcolor(BC_DarkWhite);
		console::gotoXY(40, 19); cout << "*                  1.Login                 *" << endl;
		console::gotoXY(40, 20); cout << "*                  2.Sign up               *" << endl;
		console::gotoXY(40, 21); cout << "*                  3.Play                  *" << endl;
		console::gotoXY(40, 22); cout << "*                  4.Show info             *" << endl;
		console::gotoXY(40, 23); cout << "*                  5.Replay                *" << endl;
		console::gotoXY(40, 24); cout << "*                  0.Exit                  *" << endl;
		console::gotoXY(40, 25); cout << "********************************************" << endl;

		console::gotoXY(40, 26); cout << "Please choice:";
		cin >> chose;
		cout << endl;

		if (cin.fail())
		{
			console::gotoXY(40, 27);
			cout << "Please enter again";
			std::cin.clear();
			cin.ignore();
			loop = 1;
		}
		else if ((chose < 0) || (chose > 5))
		{
			loop = 1;
		}
		else
		{
			loop = 0;
		}
		cin.ignore();

	} while (loop);
}


void menuview::MenuPlayOffline(int& chose)
{
	bool loop = 0;

	do
	{
		system("cls");
		PrintCaro();
		cout << "\n";

		console::gotoXY(40, 17); cout << "********************************************" << endl; console::Textcolor(BC_DarkYellow);
		console::gotoXY(40, 18); cout << "*     ---OFFLINE------------OFFLINE---     *" << endl; console::Textcolor(BC_DarkWhite);
		console::gotoXY(40, 19); cout << "*                  1.Login                 *" << endl;
		console::gotoXY(40, 20); cout << "*                  2.Sign up               *" << endl;
		console::gotoXY(40, 21); cout << "*                  3.Play                  *" << endl;
		console::gotoXY(40, 22); cout << "*                  4.Show info             *" << endl;
		console::gotoXY(40, 23); cout << "*                  5.Replay                *" << endl;
		console::gotoXY(40, 24); cout << "*                  0.Exit                  *" << endl;
		console::gotoXY(40, 25); cout << "********************************************" << endl;

		console::gotoXY(40, 26); cout << "Please choice:";
		cin >> chose;
		cout << endl;

		if (cin.fail())
		{
			console::gotoXY(40, 27);
			cout << "Please enter again";
			std::cin.clear();
			cin.ignore();
			loop = 1;
		}
		else if ((chose < 0) || (chose > 5))
		{
			loop = 1;
		}
		else
		{
			loop = 0;
		}
		cin.ignore();
	} while (loop);
}


void menuview::PrintCaro()
{
	int x = 25, y = 0;
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x, y);				   std::cout << "ooooooooooooo";
	console::gotoXY(x - 3, y + 1);			std::cout << "oooooooooooooooo";
	console::gotoXY(x - 5, y + 2);    std::cout << "oooooooooooooooooo";
	console::gotoXY(x - 6, y + 3);   std::cout << "ooooooooooooooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x - 7, y + 4);  std::cout << "ooooooo";
	console::gotoXY(x - 8, y + 5); std::cout << "ooooooo";
	console::gotoXY(x - 8, y + 6); std::cout << "ooooooo";
	console::gotoXY(x - 8, y + 7); std::cout << "ooooooo";
	console::gotoXY(x - 8, y + 8); std::cout << "ooooooo";
	console::gotoXY(x - 8, y + 9); std::cout << "ooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x - 8, y + 10); std::cout << "ooooooo";
	console::gotoXY(x - 7, y + 11); std::cout << "ooooooo";
	console::gotoXY(x - 6, y + 12);  std::cout << "ooooooooooooooooooo";
	console::gotoXY(x - 5, y + 13);   std::cout << "oooooooooooooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x - 3, y + 14);		std::cout << "oooooooooooooooo";
	console::gotoXY(x, y + 15);			   std::cout << "ooooooooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x - 4 + 22, y + 4);				    std::cout << "ooooooooooo";
	console::gotoXY(x - 4 + 22 - 2, y + 5);		      std::cout << "ooooooooooooooo";
	console::gotoXY(x - 4 + 22 - 3, y + 6);		     std::cout << "ooooooooooooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x - 4 + 22 - 3, y + 7);			 std::cout << "ooooooooooooooooo";
	console::gotoXY(x - 4 + 22 - 3, y + 8);			 std::cout << "oooooo     oooooo";
	console::gotoXY(x - 4 + 22 - 3, y + 9);			 std::cout << "oooooo     oooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x - 4 + 22 - 3, y + 10);		 std::cout << "oooooo     oooooo";
	console::gotoXY(x - 4 + 22 - 3, y + 11);		 std::cout << "ooooooooooooooooo";
	console::gotoXY(x - 4 + 22 - 3, y + 12);		 std::cout << "oooooo     oooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x - 4 + 22 - 3, y + 13);		 std::cout << "oooooo     oooooo";
	console::gotoXY(x - 4 + 22 - 3, y + 14);		 std::cout << "oooooo     oooooo";
	console::gotoXY(x - 4 + 22 - 3, y + 15);		 std::cout << "oooooo     oooooo";

	console::Textcolor(rand() % 15 + 1);

	console::gotoXY(x + 33, y + 4);			std::cout << "ooooo   ooooooooo";
	console::gotoXY(x + 33, y + 5);			std::cout << "oooooooooooooooooo";
	console::gotoXY(x + 33, y + 6);			std::cout << "ooooooooooooooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x + 33, y + 7);			std::cout << "oooooooooooooooooooo";
	console::gotoXY(x + 1 + 33, y + 8);			 std::cout << "ooooooo     ooooooo";
	console::gotoXY(x + 1 + 33, y + 9);			 std::cout << "ooooooo     ooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x + 1 + 33, y + 10);		 std::cout << "ooooooo";
	console::gotoXY(x + 1 + 33, y + 11);		 std::cout << "ooooooo";
	console::gotoXY(x + 1 + 33, y + 12);		 std::cout << "ooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x + 1 + 33, y + 13);		 std::cout << "ooooooo";
	console::gotoXY(x + 1 + 33, y + 14);		 std::cout << "ooooooo";
	console::gotoXY(x + 1 + 33, y + 15);		 std::cout << "ooooooo";
	console::Textcolor(BC_Yellow);
	console::gotoXY(x + 57, y + 4);					std::cout << "ooooooooooo";
	console::gotoXY(x + 57 - 2, y + 5);			  std::cout << "ooooooooooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x + 57 - 3, y + 6);			 std::cout << "ooooooooooooooooo";
	console::gotoXY(x + 57 - 3, y + 7);			 std::cout << "ooooooooooooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x + 57 - 3, y + 8);			 std::cout << "oooooo     oooooo";
	console::gotoXY(x + 57 - 3, y + 9);			 std::cout << "oooooo     oooooo";
	console::gotoXY(x + 57 - 3, y + 10);		 std::cout << "oooooo     oooooo";
	console::gotoXY(x + 57 - 3, y + 11);		 std::cout << "oooooo     oooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x + 57 - 3, y + 12);		 std::cout << "ooooooooooooooooo";
	console::gotoXY(x + 57 - 3, y + 13);		 std::cout << "ooooooooooooooooo";
	console::Textcolor(rand() % 15 + 1);
	console::gotoXY(x + 57 - 2, y + 14);		  std::cout << "ooooooooooooooo";
	console::gotoXY(x + 57, y + 15);				std::cout << "ooooooooooo";
	cout << endl;
	console::Textcolor(BC_DarkWhite);
}

