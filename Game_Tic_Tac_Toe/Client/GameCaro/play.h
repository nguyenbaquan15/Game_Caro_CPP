/**********************************************************/
/*
/* Mode: 
/*      Offline: with 2 player on a computer
/*      Online:  with socket TCP/IP
/*
/**********************************************************/
#pragma once

#include "connectserver.h"

class play
{
    private:

    public:

        /* Offline with 2 player on a computer */
        void PlayOffline(player *Player1, player* Player2);

        /* Online with socket */
        void PlayOnline(connectSever *Client, player *Player);

        /* Enter and check Position */
        void EnterPosition(chesstable* Table, int* PosX, int* PosY);

};
