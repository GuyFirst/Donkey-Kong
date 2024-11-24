



#pragma once
#include "gameConfig.h"
#include "gameBoard.h"


class Mario
{
	char m_mario = '@';
	int m_x = (gameBoard::MIN_X + gameBoard::GAME_WIDTH) / 2;
	int m_y = gameBoard::MIN_Y + gameBoard::GAME_HEIGHT - 1;
	int m_diff_x = 0;
	int m_diff_y = 0;
	bool m_isJumping;
	int m_jumpHeight;
	int m_originalY;
	gameConfig::eKeys m_lastKey;
public:
	void draw(char);
	void move(gameConfig::eKeys key);
	void jump();
};

