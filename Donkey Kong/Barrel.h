#pragma once
#include "gameConfig.h"
#include "Map.h"

class Barrel
{
	enum class numbers { MAX_BARRELS = 7 };
	int m_x = (int)gameConfig::Pos::BARREL_X_START; //first apperance of any barrel
	int m_y = (int)gameConfig::Pos::BARREL_Y_START;
	int m_diff_x = (int)gameConfig::Direction::STAY;
	int m_diff_y = (int)gameConfig::Direction::POSITIVE;
	int m_prev_diff_x = 0;

public:
	Map* map;
	void move();
	void draw(char ch);
	bool isOnFloor(char& refFloor);
	void addBarrel(Barrel barrelArr[(int)numbers::MAX_BARRELS], int size);
	void removeBarrel(Barrel* barrelArr[(int)numbers::MAX_BARRELS], int size);
	bool isOnAir(char& refFloor);
	bool isNearWall(int dirX);
	char getMapChar() { return this->map->originalMap[m_y][m_x]; }
	void reset();
};

