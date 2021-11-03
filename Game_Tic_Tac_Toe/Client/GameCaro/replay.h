/**********************************************************/
/*
/* Function: Handle file.txt. Replay match
/*
/**********************************************************/
#pragma once

#include <fstream>

class replay
{
	private:
		std::fstream File;

	public:

		/* Open file to read */
		void OpenRead();

		/* Open file to write */
		void OpenWrite();

		/* Close file */
		void Close();

		/* Read 1 line in file */
		void Read(std::string *Data);

		/* Write a line to file */
		void Write(std::string Data);

		/* Check end line of file */
		bool isEndFile();

		/* Split data received */
		void SplitData(std::string StrIn, std::string* StrOut, char Character);
};