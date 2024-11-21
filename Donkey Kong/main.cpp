#include "gameConfig.h"
#include "Mario.h"
#include "general.h"
#include <conio.h> //for kbhit_ getch
#include <Windows.h>


//we did a mario that moved to our keyboard response/
//we need to realize why is the x moving slower than the y
//and also make a real border for the game
int main()
{
    Mario mario;
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
		Sleep(50);
		mario.draw(' ');
		mario.move((gameConfig::eKeys)keyPressed);
	}
	
}


