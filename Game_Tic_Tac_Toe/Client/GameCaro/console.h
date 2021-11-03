/**********************************************************/
/*
/* Function: Work with Console screen
/*
/**********************************************************/
#pragma once


/* Define color */
#define BC_Black		0
#define BC_DarkBlue		1
#define BC_DarkGreen	2
#define BC_DarkCyan		3
#define BC_DarkRed		4
#define BC_DarkPink		5
#define BC_DarkYellow	6
#define BC_DarkWhite	7
#define BC_Grey			8
#define BC_Blue			9
#define BC_Green		10
#define BC_Cyan			11
#define BC_Red			12
#define BC_Pink			13
#define BC_Yellow		14
#define BC_White		15
#define BC_defaultColor	7 


class console
{
	private:

	public:

		/* Fix Console */
		static void fixConsoleWindow();

		/* Move to position on Console */
		static void gotoXY(int, int);

		/* Edit size of Console */
		static void setConsoleWindow(int w, int h);

		/* Display mouse of Console */
		static void DisplayMouse();

		/* Hide mouse of Console*/
		static void HideMouse();

		/* Set color on console */
		static void Textcolor(int color);

};

