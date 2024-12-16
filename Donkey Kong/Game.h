#pragma once
#include "Mario.h"
#include "Map.h"
#include "menu.h"
#include "Barrel.h"

class Game
{
public:
	void run();
	int startGame();
	void pause();
	void loseALife();
	void win();
	void lose();
	void drawMario(Mario& mario);
	bool handleLifeLoss(int& currLives, Mario& mario, Map& gameBoard, int& barrelCurr, int& barrelCounter, bool& isMarioLocked);
	void spawnBarrel(Barrel arrBarrels[], int& barrelCurr, Map& gameBoard);
	void moveBarrels(Barrel arrBarrels[], int barrelCurr, Mario& mario);
	void handleMarioLocked(char keyPressed, Mario& mario, bool& isMarioLocked);
	bool isMarioInLongAction(Mario& mario);
	bool isMarioInShortAction(Mario& mario);
	void toggleArrow(Map& gameBoard, const Point& point);
};

