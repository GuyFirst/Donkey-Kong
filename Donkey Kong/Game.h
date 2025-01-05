#pragma once
#include <vector>
#include "Ghost.h"
#include "Mario.h"
#include "Map.h"
#include "menu.h"
#include "Barrel.h"
#include <iomanip>      
#include <thread> 

class Game
{
public:
	void run();
	int startGame();
	void pause(bool& isPaused, std::chrono::steady_clock::duration& pausedTime);
	void loseALife() const;
	void win() const;
	void lose() const;
	void drawMario(Mario& mario);
	bool handleLifeLoss(int& currLives, Mario& mario, Map& gameBoard, static int& barrelCurr, static int& barrelCounter, bool& isMarioLocked, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, int& score);
	void spawnBarrel(std::vector<Barrel>& barrels, int& barrelCurr, Map& gameBoard);
	void moveBarrels(std::vector<Barrel>& barrels, int barrelCurr, Mario& mario);
	void handleMarioLocked(char keyPressed, Mario& mario, bool& isMarioLocked);
	bool isMarioInLongAction(Mario& mario) const;
	bool isMarioInShortAction(Mario& mario) const;
	void toggleArrow(Map& gameBoard, const Point& point);
	void spawnGhosts(std::vector<Ghost>& ghosts, Map& gameBoard);
	void moveGhosts(std::vector<Ghost>& ghosts);
	void resetGhosts(std::vector<Ghost>& ghosts);
	std::vector<Point> defineFloorsToToggle(Map& map);
	void patishDestroy(std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts, Mario& mario, char key);
	void updateClock(const std::chrono::seconds& elapsedTime);
};

