#include <string>
#include <iomanip>
#include "player.h"


player::player()
{
    /* do nothing */
}


player::player(int Character)
{
    this->Character = Character;
}


void player::EnterPlayer()
{
    cout << "Name:";
    //cin.ignore();
    getline(cin, Info.Name);
    cout << "Age:";
    cin >> Info.Age;
    cout << "Sex:";
    cin.ignore();
    getline(cin, Info.Sex);
}


void player::DisplayPlayer()
{
    cout << "-------------------------------------------------------------------" << endl;

    cout << " _________________________________________________________________" << endl;
    cout << "|         Name         |  Age  |  Sex  |  Win  |  Lose  |  Equal  |" << endl;
    cout << "|______________________|_______|_______|_______|________|_________|" << endl;
    cout << "|" << setw(26) << left << Info.Name;
    cout<< setw(7)<<left<<Info.Age;
    cout << setw(9) << left << Info.Sex;
    cout << setw(8) << left << Info.Win;
    cout << setw(9) << left << Info.Lose;
    cout << setw(8) << left << Info.Equal << endl;
    cout << "|______________________|_______|_______|_______|________|_________|" << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
 
}


infoplayer_t player::GetInfo()
{
    return Info;
}


void player::SetInfo(infoplayer_t Info)
{
    this->Info.Name = Info.Name;
    this->Info.Age= Info.Age;
    this->Info.Sex = Info.Sex;
    this->Info.Win = Info.Win;
    this->Info.Lose = Info.Lose;
    this->Info.Equal = Info.Equal;
}


void player::SetPosX(int PosX)
{
    this->PosX = PosX;
}


void player::SetPosY(int PosY)
{
    this->PosY = PosY;
}


int player::GetPosX()
{
    return PosX;
}


int player::GetPosY()
{
    return PosY;
}


int player::GetCharacter()
{
    return Character;
}


void player::SetCharacter(int Character)
{
    this->Character = Character;
}


void player::SetWin()
{
    this->Info.Win += 1;
}


void player::SetLose()
{
    this->Info.Lose += 1;
}


void player::SetEqual()
{
    this->Info.Equal += 1;
}