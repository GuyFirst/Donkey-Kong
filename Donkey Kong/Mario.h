#pragma once
#include "gameConfig.h"
#include "gameBoard.h"
class Mario
{
	char m_mario = '@';
	int m_x = (gameBoard::MIN_X+gameBoard::GAME_WIDTH) / 2;
	int m_y = gameBoard::MIN_Y+gameBoard::GAME_HEIGHT - 1;
	int m_diff_x = 1;//(int)gameConfig::eKeys::STAY;
	int m_diff_y = 0;// (int)gameConfig::eKeys::STAY;
public:
	void draw(char);
	void move(gameConfig::eKeys key);
};


