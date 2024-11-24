#include <iostream>
#include <Windows.h>

#include "Mario.h"

#include "general.h"




void Mario::draw(char ch)
{
	gotoxy(m_x, m_y);
	std::cout << ch;
}



void Mario::move(gameConfig::eKeys key)
{
	static int counter = 0;
	switch (key)
	{
	case gameConfig::eKeys::LEFT:
		m_diff_x = -1;
		m_diff_y = 0;
		break;
	case gameConfig::eKeys::RIGHT:
		m_diff_x = 1;
		m_diff_y = 0;
		break;
	case gameConfig::eKeys::UP:
		m_diff_y = -1;
		break;
	case gameConfig::eKeys::DOWN:
		m_diff_x = 0;
		m_diff_y = 1;
		break;
	case gameConfig::eKeys::STAY:
		m_diff_x = 0;
		m_diff_y = 0;
		break;
	}
	if ((m_x > gameBoard::MIN_X + gameBoard::GAME_WIDTH - 2 && key == gameConfig::eKeys::RIGHT) || (m_x < gameBoard::MIN_X + 3 && key == gameConfig::eKeys::LEFT))
		m_diff_x = 0;
	m_x += m_diff_x;



	if ((m_y > gameBoard::MIN_Y + gameBoard::GAME_HEIGHT - 2 && key == gameConfig::eKeys::DOWN) || (m_y < gameBoard::MIN_Y + 2 && key == gameConfig::eKeys::UP))
		m_diff_y = 0;
	m_y += m_diff_y;
}

void Mario::jump()
{
}
