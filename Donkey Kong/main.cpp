#include "gameConfig.h"
#include "Mario.h"
#include "general.h"
#include <conio.h> //for kbhit_ getch
#include <Windows.h>
#include "gameBoard.h"
#include "point.h"



int main()
{
	ShowConsoleCursor(false);
	gameBoard game;
	game.draw();
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
		Sleep(30);
		mario.draw(' ');
		mario.move((gameConfig::eKeys)keyPressed);
		
	}
	
	gotoxy(0, game.GAME_HEIGHT + game.MIN_Y + 2);
}


