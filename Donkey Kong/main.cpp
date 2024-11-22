﻿#include "gameConfig.h"
#include "Mario.h"
#include "general.h"
#include <conio.h> //for kbhit_ getch
#include <Windows.h>
#include "Map.h"
#include "point.h"



int main()
{
	ShowConsoleCursor(false);
	Map map;
	map.draw();
	Mario mario;
	char keyPressed = (char)(gameConfig::eKeys::STAY);
	while (true)
	{
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (int)gameConfig::eKeys::ESC)
				break;
		}
		mario.draw('@');
		Sleep(80);
		mario.draw(' ');
		mario.move((gameConfig::eKeys)keyPressed);

	}

	gotoxy(0, map.GAME_HEIGHT + map.MIN_Y + 2);
}
