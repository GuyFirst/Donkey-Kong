#pragma once
#include "gameConfig.h"
class Mario
{
	char m_mario = '@';
	int m_x = 4;
	int m_y = 0;
	int m_diff_x = 1;//(int)gameConfig::eKeys::STAY;
	int m_diff_y = 0;// (int)gameConfig::eKeys::STAY;
public:
	void draw(char);
	void move(gameConfig::eKeys key);
};


