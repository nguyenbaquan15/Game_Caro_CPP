#include "chesstable.h"
#include "player.h"
#include "checkwin.h"


char checkwin::Result = -1;


void checkwin::Win(chesstable& Table, player* Player)
{
    int CountRow = 0;
    int CountCol = 0;
    int CountCrossR= 0;
    int CountCrossL = 0;
    int i = 1;


    /* Check horizontal */
    /*----------------------------------------------------------------------*/
    while (Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY())\
        == Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY() + i))
    {
        CountRow++;
        i++;
    }

    i = 1;
    while (Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY())\
        == Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY() - i))
    {
        CountRow++;
        i++;
    }
    /*----------------------------------------------------------------------*/


    /* Check vertical */
    /*----------------------------------------------------------------------*/
    i = 1;
    while (Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY())\
        == Table.GetValuePosXY(Player->GetPosX()+i, Player->GetPosY()))
    {
        CountCol++;
        i++;
    }

    i = 1;
    while (Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY())\
        == Table.GetValuePosXY(Player->GetPosX() - i, Player->GetPosY()))
    {
        CountCol++;
        i++;
    }
    /*----------------------------------------------------------------------*/


    /* Check cross */
    /*----------------------------------------------------------------------*/
    i = 1;
    while (Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY())\
        == Table.GetValuePosXY(Player->GetPosX() - i, Player->GetPosY()+i))
    {
        CountCrossR++;
        i++;
    }

    i = 1;
    while (Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY())\
        == Table.GetValuePosXY(Player->GetPosX() + i, Player->GetPosY() - i))
    {
        CountCrossR++;
        i++;
    }
    /*----------------------------------------------------------------------*/


    /* Check cross */
    /*----------------------------------------------------------------------*/
    i = 1;
    while (Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY())\
        == Table.GetValuePosXY(Player->GetPosX() - i, Player->GetPosY() - i))
    {
        CountCrossL++;
        i++;
    }

    i = 1;
    while (Table.GetValuePosXY(Player->GetPosX(), Player->GetPosY())\
        == Table.GetValuePosXY(Player->GetPosX() + i, Player->GetPosY() + i))
    {
        CountCrossL++;
        i++;
    }
    /*----------------------------------------------------------------------*/

    /* Check condition win */
    if ((CountRow >= 3) || (CountCol >= 3) || (CountCrossR >= 3) || (CountCrossL >= 3))
    {
        checkwin::Result = 1;
    }

    /* Check condition Equal */
    if (Table.isFullTable())
    {
        checkwin::Result = 0;
    }
}


int checkwin::GetResult()
{
    return checkwin::Result;
}


void checkwin::ResetResult()
{
    checkwin::Result = -1;
}