
#include <iostream>
#include <string>
#include <fstream>

#include "replay.h"


void replay::OpenRead()
{
	File.open("Replay.txt",std::ios::in);
}


void replay::OpenWrite()
{
	File.open("Replay.txt",std::ios::out);
}


void replay::Close()
{
	File.close();
}


void replay::Read(std::string *Data)
{
	if (File.is_open())
	{
		/*Read a line in file */
		File >> (*Data);
	}

}


void replay::Write(std::string Data)
{

	if (File.is_open())
	{
		/* Write a line in file */
		File << Data << std::endl;
	}
}


bool replay::isEndFile()
{
	return File.eof();
}


void replay::SplitData(std::string StrIn, std::string* StrOut, char Character)
{
	int i = 0;
	int j = 0;

	while (StrIn[i] != NULL)
	{
		if (StrIn[i] != Character)
		{
			StrOut[j] += StrIn[i];
		}
		else
		{
			j++;
		}
		i++;
	}
}
