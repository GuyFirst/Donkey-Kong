#pragma once
#include "Mario.h"
#include "Map.h"
#include "menu.h"

class Game
{
public:
	void run();
	int startGame();
	void pause();
	void loseALife();
	void win();
	void lose();
};

