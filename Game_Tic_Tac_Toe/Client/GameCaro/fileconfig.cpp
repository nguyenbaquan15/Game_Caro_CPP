#include <iostream>
#include <fstream>
#include <windows.h>
#include <TCHAR.h>
#include <sstream>

#include "player.h"
#include "fileconfig.h"

using namespace std;

#define     NAMEFILE    "test.ini"
#define     PATHFILE    ".\\test.ini"


void fileconfig::Open()
{
    //File.open("test.ini");
}


void fileconfig::Close()
{
    //File.close();
}


void fileconfig::WriteString(string Section, string Key, string Value)
{
    /* Write data type string */
    WritePrivateProfileStringA(Section.c_str(), Key.c_str(),
                              Value.c_str(), PATHFILE);
}


void fileconfig::WriteInt(string Section, string Key, int Value)
{
    /* Write data type integer */
    ostringstream convert;
    convert << Value;
    string TValue = convert.str();

    WritePrivateProfileStringA(Section.c_str(), Key.c_str(),TValue.c_str(),PATHFILE);
}


string fileconfig::ReadString(string Section, string Key)
{
    string Result;
    char Buffer[20];

    /* Read data type string */
    GetPrivateProfileStringA(Section.c_str(), Key.c_str(),"default",\
        Buffer, 20,PATHFILE);

    Result = convertToString(Buffer,sizeof(Buffer));

    return Result;
}


int fileconfig::ReadInt(string Section, string Key)
{
    int Result;

    /* Read data type integer */
    Result =GetPrivateProfileIntA(Section.c_str(), Key.c_str(), 0, PATHFILE);

    return Result;
}


int fileconfig::LogIn(string UserName, string PassWord, int *Position)
{
    bool finish = 0;
    int Result=0;
    int Count = 0;
    bool CheckUser=0;
    bool CheckPass=0;

    string SCount;
    string Tdefault = "default";

    /* Scan file.ini to find Account */
    while (finish == 0)
    {
        Count++;
        SCount = convertIntToString(Count);

        if ((UserName.compare(this->ReadString(SCount, "User")) == 0))
        {
            CheckUser = 1;
            *Position = Count;
        }

        if ((PassWord.compare(this->ReadString(SCount, "Pass")) == 0))
        {
            CheckPass = 1;
        }

        if ((Tdefault.compare(this->ReadString(SCount, "User")) == 0))
        {
            finish = 1;
        }
    }

    /* Check Account */
    if (CheckUser && CheckPass)
    {
        Result = 1;
    }
    else if ((CheckUser) && (!CheckPass))
    {
        Result = 0;
    }
    else if (!CheckUser)
    {
        Result = 2;
    }

    return Result;

}


int fileconfig::SignUp(string UserName, string PassWord)
{
    int Result;
    int Count;
    int Position;

    /* Check account in File.ini */
    Result = this->LogIn(UserName, PassWord, &Position);

    if (2==Result)
    {
        /* Read total number of player in File.ini */
        Count = this->ReadInt("Config", "Count");
        Count++;

        this->WriteString(to_string(Count), "ID", to_string(Count));
        this->WriteString(to_string(Count), "User", UserName);
        this->WriteString(to_string(Count), "Pass", PassWord);
        this->WriteInt(to_string(Count), "Age", 0);
        this->WriteString(to_string(Count), "Sex", "Male");
        this->WriteInt(to_string(Count), "Win", 0);
        this->WriteInt(to_string(Count), "Lose", 0);
        this->WriteInt(to_string(Count), "Equal", 0);

        /* Update number of player in File.ini */
        this->WriteInt("Config","Count",Count);

        Result = 3;
    }

    return Result;
}


void fileconfig::ReadPlayer(int Index, player* Player)
{
    infoplayer_t Info;

    string SIndex = convertIntToString(Index);

    /* Read information of player */
    Info.ID = this->ReadInt(SIndex, "ID");
    Info.Name = this->ReadString(SIndex, "User");
    Info.Age = this->ReadInt(SIndex, "Age");
    Info.Sex = this->ReadString(SIndex, "Sex");
    Info.Win = this->ReadInt(SIndex, "Win");
    Info.Lose = this->ReadInt(SIndex, "Lose");
    Info.Equal = this->ReadInt(SIndex, "Equal");

    Player->SetInfo(Info);
}


void fileconfig::WritePlayer(player *Player)
{
    infoplayer_t Info;

    Info = Player->GetInfo();

    ostringstream convert;
    convert << Info.ID;
    string InfoCount = convert.str();

    /* Write information of player */
    this->WriteInt(InfoCount, "Win", Info.Win);
    this->WriteInt(InfoCount, "Lose", Info.Lose);
    this->WriteInt(InfoCount, "Equal", Info.Equal);

}


void fileconfig::FindPlayerSame(player *Player)
{
    bool finish = 0;
    int Count = 0;
    int diffwin;
    int difflose;

    string SCount;
    string Tdefault = "default";


    while (finish == 0)
    {
        Count++;
        SCount = convertIntToString(Count);

        if (Count == 1)
        {
            diffwin = this->ReadInt(SCount, "Win") - Player->GetInfo().Win;
            difflose = this->ReadInt(SCount, "Lose") - Player->GetInfo().Win;
        }

        if (diffwin > (this->ReadInt(SCount, "Win") - Player->GetInfo().Win))
        {
            diffwin = this->ReadInt(SCount, "Win") - Player->GetInfo().Win;

        }

        if (difflose > (this->ReadInt(SCount, "Lose") - Player->GetInfo().Lose))
        {
            difflose = this->ReadInt(SCount, "Lose") - Player->GetInfo().Lose;

        }
    }

    /* Haven't complete */
}


string fileconfig::convertToString(char* a, int size)
{
    string s(a);

    return s;
}


string fileconfig::convertIntToString(int a)
{
    ostringstream convert;
    convert << a;
    string Index = convert.str();

    return Index;
}