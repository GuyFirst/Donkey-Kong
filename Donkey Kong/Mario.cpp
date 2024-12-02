#include <iostream>
#include <Windows.h>

#include "Mario.h"
#include "gameConfig.h"
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
		m_diff_x = (int)gameConfig::Direction::NEGATIVE;
		m_diff_y = 0;
		break;
	case gameConfig::eKeys::RIGHT:
		m_diff_x = (int)gameConfig::Direction::POSITIVE;
		m_diff_y = 0;
		break;
	case gameConfig::eKeys::UP:
		if (isUnderLadder()) {
			climb();
			break;
		}
		if (isOnFloor())
			jump();
		break;
	case gameConfig::eKeys::DOWN:
		if (isOnLadder())
			downLadder();
		m_diff_y = (int)gameConfig::Direction::POSITIVE;
		break;
	case gameConfig::eKeys::STAY:
		m_diff_x = 0;
		m_diff_y = 0;
		return;
	}
	if (isNearWall(m_diff_x))
	{
		m_diff_x = 0;
	}

	if (!isOnFloor())
	{
		m_diff_y = 1;
	}
	else
		m_diff_y = 0;

	m_x += m_diff_x;
	m_y += m_diff_y;

}

void Mario::jump()
{
	char curr = this->getMapChar();
	int jumpHeight = 2;
	m_diff_y = (int)gameConfig::Direction::NEGATIVE;
	for (int i = 0; i < jumpHeight; i++)
	{
		if (isNearWall(m_diff_x))
			m_diff_x = 0;
		if (isUnderFloor()) {
			this->draw(curr);
			return;
		}
		if (curr == 'H')
			this->draw('H');
		else
			this->draw(curr);
		m_x += m_diff_x;
		m_y += m_diff_y;
		curr = this->getMapChar();
		if (curr == 'H')
			this->draw('#');
		else
			this->draw('@');
		Sleep(gameConfig::SLEEP_DURATION);
	}
	m_diff_y = 0;
	this->draw(curr);
}

bool Mario::isNearWall(int dirX)
{
	if (dirX == (int)gameConfig::Direction::POSITIVE)
	{
		if (m_x > gameConfig::GAME_WIDTH - 4)
			return true;
	}
	else
	{
		if (m_x <= 0)
			return true;
	}
	return false;

}

bool Mario::isOnFloor()
{
	if (this->map->currentMap[m_y + 1][m_x] != ' ')
		return true;
	return false;
}

bool Mario::isUnderFloor()
{
	if (this->map->currentMap[m_y - 1][m_x] != ' ')
		return true;
	return false;
}

bool Mario::isNearPaulina()
{
	if (this->map->currentMap[m_y][m_x + m_diff_x] == '$')
		return true;
	return false;
}

char Mario::getMapChar()
{
	return this->map->originalMap[m_y][m_x];
}

bool Mario::isUnderLadder()
{
	if (this->map->currentMap[m_y - 1][m_x] == 'H')
		return true;
	return false;
}

bool Mario::isOnLadder()
{
	if (this->map->currentMap[m_y + 2][m_x] == 'H')
		return true;
	return false;
}

void Mario::climb()
{
	this->m_diff_y = (int)gameConfig::Direction::NEGATIVE;
	while (this->map->currentMap[m_y][m_x] == 'H')
	{
		this->draw('H');
		m_y += m_diff_y;
		this->draw('#');
		Sleep(gameConfig::SLEEP_DURATION);
	}
	char curr = this->getMapChar();
	this->draw(curr);
	m_y += m_diff_y;
	this->draw('#');
	Sleep(gameConfig::SLEEP_DURATION);
	this->draw(' ');
}

void Mario::downLadder()
{
	this->m_diff_y = (int)gameConfig::Direction::POSITIVE;
	while (this->map->currentMap[m_y + 2][m_x] == 'H') {
		char curr = this->getMapChar();
		this->draw(curr);
		m_y += m_diff_y;
		this->draw('#');
		Sleep(gameConfig::SLEEP_DURATION);
	}
	char curr = this->getMapChar();
	this->draw(curr);
	m_y += m_diff_y;
	this->draw('#');
	Sleep(gameConfig::SLEEP_DURATION);
}
