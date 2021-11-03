/**********************************************************/
/* 
/* configuration file's Library (File.ini)
/* Function: use to read/write information to file.ini
/* 
/**********************************************************/
#pragma once

#include <fstream>
#include <windows.h>
#include <TCHAR.h>

class fileconfig
{
	private:
		fstream File;

	public:
		void Open();
		void Close();

		/* Write a string into file config */
		void WriteString(string Section, string Key, string Value);

		/* Write a integer number into file config */
		void WriteInt(string Section, string Key, int Value);

		/* Read a string from file config */
		string ReadString(string Section, string Key);

		/* Read a integer number from file config */
		int ReadInt(string Section, string Key);

		/* Handle require Login */
		int LogIn(string UserName, string PassWord, int* Position);

		/* Handle require Sign up */
		int SignUp(string UserName, string PassWord);

		/* Write information of player to file config */
		void WritePlayer(player *Player);

		/* Read information of player to file config */
		void ReadPlayer(int Index, player* Player);

		/* Read information of player with user name */
		void ReadInfoPlayer(string Name);

		/* Find player same level */
		void FindPlayerSame(player *Player);

		/* Convert char[] -> String */
		string convertToString(char* a, int size);

		/* Convert int -> string */
		string convertIntToString(int a);

};