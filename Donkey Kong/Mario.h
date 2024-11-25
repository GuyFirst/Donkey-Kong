



#pragma once
#include "gameConfig.h"
#include "Map.h"


class Mario
{
	char m_mario = '@';
	int m_x = (Map::MIN_X + Map::GAME_WIDTH) / 2;
	int m_y = Map::MIN_Y + Map::GAME_HEIGHT - 2;
	int m_diff_x = 0;
	int m_diff_y = 0;
	bool m_isJumping;
	int m_jumpHeight;
	int m_originalY;
public:
	void draw(char);
	void move(gameConfig::eKeys key);
	void jump();
};

