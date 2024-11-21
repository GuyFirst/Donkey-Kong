#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>


void gotoxy(int x, int y) {

	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void clrsrc()
{
	system("cls");
}