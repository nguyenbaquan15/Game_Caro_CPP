#include <iostream>
#include <thread>

#include "control.h"

int main()
{

    //thread ClientDisconnect;
    //thread Main;

    controll menu("127.0.0.1", 1000);
    menu.chosemenu();

    return 0;
}