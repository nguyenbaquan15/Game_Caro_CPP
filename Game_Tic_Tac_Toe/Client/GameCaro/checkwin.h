/**********************************************************/
/*
/* Function: check winner/loser in match
/* 
/**********************************************************/
#pragma once

class checkwin
{
    private:
        /* Variable save result after check */
        static char Result;

    public:
        /* Check winer */
        static void Win(chesstable& Table, player* Player);

        /* Received result */
        static int GetResult();

        /* Set result=-1 */
        static void ResetResult();

};