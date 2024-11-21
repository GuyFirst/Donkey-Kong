#include "Mario.h"
#include <iostream>
#include "general.h"


void Mario::draw(char ch)
{
	gotoxy(m_x, m_y);
	std::cout << ch;
}

void Mario::move(gameConfig::eKeys key)
{
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
		m_diff_x = 0;
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
	m_x += m_diff_x;
	if (m_x > 78 || m_x < 3)
		m_diff_x = 0;

	m_y += m_diff_y;
	if (m_y > 25 || m_y < 2)
		m_diff_y = 0;
}
