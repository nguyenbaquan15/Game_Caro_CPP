#include <iostream>
#include "chesstable.h"
#include "console.h"

using namespace std;


chesstable::chesstable(int Row, int Col)
{
    this->Row = Row;
    this->Col= Col;
}


void chesstable::Init()
{
    cout << "Please enter: row, column:";
    cin >>  Row >> Col;
    cin.ignore();
}


void chesstable::SetPos(int PosX, int PosY, int Character)
{
    arr[PosX][PosY] = Character;
}


int chesstable::GetValuePosXY(int PosX, int PosY)
{
    return arr[PosX][PosY];
}


void chesstable::SetCount()
{
    this->Count += 1;
}


bool chesstable::isFullTable()
{
    if (Count == (Row * Col))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void chesstable::Display()
{
    int x = 25;
    int y = 0;
    cout << '\a';
    console::Textcolor(BC_Green);
    console::gotoXY(x + 15, y+1); cout << "..........................................." << endl;
    console::gotoXY(x + 15, y+2); cout << ".                                         ." << endl;
    console::gotoXY(x + 15, y+3); cout << ".                    FIGHT                ." << endl;
    console::gotoXY(x + 15, y+4); cout << ".         Player1 <x> - Player2 <o>       ." << endl;
    console::gotoXY(x + 15, y+5); cout << ".                                         ." << endl;
    console::gotoXY(x + 15, y+6); cout << "..........................................." << endl;
    console::Textcolor(BC_DarkWhite);

    console::gotoXY(x + 15, y + 7); cout << "   |";
    for (int i = 0; i < Col; i++)
    {
        cout << " " << i << " |";
    }
    cout << "\n";

    console::gotoXY(x + 15, y + 8);
    for (int j = 0; j <= Col; j++)
    {
        cout << "----";
    }
    cout << "\n";


    /* Print chess table on screen */
    for (int i = 0; i < Row; i++)
    {
        console::gotoXY(x + 15, (y + 9)+(i*2));
        cout << "|" << i << " |";

        for (int j = 0; j < Col; j++)
        {
            if ((arr[i][j] != 'x') && (arr[i][j] != 'o'))
            {
                cout << "   |";
            }
            else
            {
                if (arr[i][j] == 'x')
                {
                    console::Textcolor(BC_Red);
                    cout << " " << (char)arr[i][j];
                    console::Textcolor(BC_DarkWhite);
                }
                else
                {
                    console::Textcolor(BC_Yellow);
                    cout << " " << (char)arr[i][j];
                    console::Textcolor(BC_DarkWhite);
                }
                cout<< " |";
            }

        }
        cout << "\n";

        console::gotoXY(x + 15, y + 10+(i*2));
        for (int j = 0; j <= Col; j++)
        {
            cout << "----";
        }
        cout << "\n";

    }

    console::gotoXY(x + 15, y + 10+ (Row*2));
}
