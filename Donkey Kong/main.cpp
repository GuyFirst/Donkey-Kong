#include "gameConfig.h"
#include "Mario.h"
#include "general.h"
#include <conio.h> //for kbhit_ getch
#include <Windows.h>
#include "gameBoard.h"
#include "point.h"

//we did a mario that moved to our keyboard response/
//we need to realize why is the x moving slower than the y
//and also make a real border for the game


int main()
{
	point p[4];
	p[0].init(2, 2);
	p[1].init(78, 2);
	p[2].init(78, 23);
	p[3].init(2,23);

	gameBoard game;
	game.draw(p);

   /* Mario mario;
	while (true)
	{
		char keyPressed = 0;
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (int)gameConfig::eKeys::ESC)
				break;
		}
		
		mario.draw('@');
		Sleep(10);
		mario.draw(' ');
		mario.move((gameConfig::eKeys)keyPressed);
	}*/
	
}


