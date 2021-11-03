/**********************************************************/
/*
/* Function: Create a player
/*
/**********************************************************/
#pragma once

#include <iostream>
using namespace std;


/* Information of player */
typedef struct infoplayer
{
    int ID = 0;
    string Name="Default";
    int Age=0;
    string Sex="Male";
    int Win = 0;
    int Equal = 0;
    int Lose = 0;

} infoplayer_t;


class player
{
    private:
        infoplayer_t Info;
        int PosX;
        int PosY;
        int Character;

    public:

        player();

        player(int character);

        /* Enter information of player from keyboard */
        void EnterPlayer();

        /* Display information of player on screen */
        void DisplayPlayer();

        /* Get information of player */
        infoplayer_t GetInfo();

        /* Set information for player */
        void SetInfo(infoplayer_t Info);

        /* Set currently coordinate X  for player */
        void SetPosX(int PosX);

        /* Set currently coordinate Y for player */
        void SetPosY(int PosY);

        /* Get currently coordinate X  for player */
        int GetPosX();

        /* Get currently coordinate Y for player */
        int GetPosY();

        /* Get 'x' or 'o' */
        int GetCharacter();

        /* Set 'x' or 'o' */
        void SetCharacter(int Character);

        /* Set Win after match end */
        void SetWin();

        /* Set Lose after match end */
        void SetLose();

        /* Set Equal after match end */
        void SetEqual();

};