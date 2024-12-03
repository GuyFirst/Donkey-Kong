
#pragma once
#include "gameConfig.h"
#include "Map.h"
#include "Barrel.h"


class Mario
{
	char m_mario = '@';
	int m_x = (int)Map::GAME_WIDTH / 2; //start point in the middle of the floor
	int m_y = (int)Map::GAME_HEIGHT - 2;//start point one character above the floor
	int m_diff_x = 0;
	int m_diff_y = 0;
	int m_countHeight = 0;

public:
	int lives = 3;
	Map* map;
	void draw(char);
	void move(gameConfig::eKeys key, Barrel b[], int barrelCurr);
	void jump(Barrel b[], int barrelCurr);
	bool isNearWall(int dirX);
	bool isOnFloor();
	bool isUnderFloor();
	bool isNearPaulina();
	char getMapChar();
	bool isUnderLadder();
	bool isOnLadder();
	void climb(Barrel b[], int barrelCurr);
	void downLadder(Barrel b[], int barrelCurr);
	void checkFallHeight();
};

