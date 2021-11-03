void Check(int arr[][10], int PosX, int PosY)
{
    int CountLR = 0;
    int CountRL = 0;
    int CountUD = 0;
    int CountDU = 0;
    int Count45 = 0;
    int Count135 = 0;
    int Count225 = 0;
    int Count315 = 0;

    /* Scan row: right -> left */
    for (int i = 1; i < 4; i++)
    {
        if (arr[PosX][PosY] == arr[PosX][PosY + i])
        {
            CountLR++;
        }
    }

    /* Scan row: left -> right */
    for (int i = 1; i < 4; i++)
    {
        if (arr[PosX][PosY] == arr[PosX][PosY - i])
        {
            CountRL++;
        }
    }

    /* Scan row: Up -> Down */
    for (int i = 1; i < 4; i++)
    {
        if (arr[PosX][PosY] == arr[PosX - i][PosY])
        {
            CountUD++;
        }
    }

    /* Scan row: Down -> Up */
    for (int i = 1; i < 4; i++)
    {
        if (arr[PosX][PosY] == arr[PosX + i][PosY])
        {
            CountDU++;
        }
    }

    /* Scan goc 45 */
    for (int i = 1; i < 4; i++)
    {
        if (arr[PosX][PosY] == arr[PosX - i][PosY + i])
        {
            Count45++;
        }
    }

    /* Scan goc 135 */
    for (int i = 1; i < 4; i++)
    {
        if (arr[PosX][PosY] == arr[PosX - i][PosY - i])
        {
            Count135++;
        }
    }

    /* Scan goc 225 */
    for (int i = 1; i < 4; i++)
    {
        if (arr[PosX][PosY] == arr[PosX + i][PosY - i])
        {
            Count225++;
        }
    }

    /* Scan goc 315 */
    for (int i = 1; i < 4; i++)
    {
        if (arr[PosX][PosY] == arr[PosX + i][PosY + i])
        {
            Count315++;
        }
    }

    if ((CountLR == 3) || (CountRL == 3) || (CountUD == 3) || (CountDU == 3)\
        || (Count45 == 3) || (Count135 == 3) || (Count225 == 3) || (Count315 == 3))
    {
        Win = 1;
    }
}