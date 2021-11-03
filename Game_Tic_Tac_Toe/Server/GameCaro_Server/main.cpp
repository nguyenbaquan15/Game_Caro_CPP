#include <iostream>

#include "multiclient.h"


int main()
{
	multiclient Server(1000);

	Server.Init();
	Server.CreateSocket();
	Server.BindIpAddr();
	Server.CreateMaster();
	Server.Listening();
	Server.RemoveListening();
	Server.MessageHappen();
	Server.CleanupWinsock();

	return 0;
}