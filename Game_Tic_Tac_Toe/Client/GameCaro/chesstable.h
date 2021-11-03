/**********************************************************/
/*
/* Function: Create a chess table
/*
/**********************************************************/
#pragma once

class chesstable
{
    private:
        int Row;
        int Col;
        int Count = 0;
        int arr[20][20] = {0};

    public:

        chesstable(int Row, int Col);

        /* Initialize chess table */
        void Init();

        /* Set position of player go */
        void SetPos(int PosX, int PosY, int character);

        /* Count number of position play */
        void SetCount();

        /* Get value of position (x or o) */
        int GetValuePosXY(int PosX, int PosY);

        /* Display chess table */
        void Display();

        /* is check chess table full */
        bool isFullTable();

};