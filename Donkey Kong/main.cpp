#include "gameConfig.h"
#include "Mario.h"
#include "general.h"
#include <conio.h> //for kbhit_ getch
#include <Windows.h>
#include "Map.h"



int main()
{
	ShowConsoleCursor(false);
	Map m;
	m.resetMap();
	m.printMap();
	Mario mario;
	mario.map = &m;
	char keyPressed = (char)(gameConfig::eKeys::STAY);
	while (true)
	{
		keyPressed = 0;
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (int)gameConfig::eKeys::ESC)
				break;
		}
		char curr = mario.getMapChar();
		if (curr == 'H')
			mario.draw('#');
		else
			mario.draw('@');
		Sleep(70);
		if (curr == 'H')
			mario.draw('H');
		else
			mario.draw(' ');

			mario.move((gameConfig::eKeys)keyPressed);
		keyPressed = 0;

	}

}
