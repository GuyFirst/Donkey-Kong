



#pragma once
#include "gameConfig.h"
#include "Map.h"


class Mario
{
	char m_mario = '@';
	int m_x = (Map::MIN_X + Map::GAME_WIDTH) / 2;
	int m_y = Map::MIN_Y + Map::GAME_HEIGHT - 3 ;
	int m_diff_x = 0;
	int m_diff_y = 0;
	
public:
	Map* map;
	void draw(char);
	void move(gameConfig::eKeys key);
	void jump();
	bool isNearBorder(gameConfig::eKeys key);
};

