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



void Mario::move(gameConfig::eKeys key, Barrel b[], int barrelCurr)
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
			climb(b, barrelCurr);
			break;
		}
		if (isOnFloor())
			jump(b, barrelCurr);
		break;
	case gameConfig::eKeys::DOWN:
		if (isOnLadder())
			downLadder(b, barrelCurr);

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
		this->m_countHeight++;
	}
	else
	{
		m_diff_y = 0;
		checkFallHeight();
		m_countHeight = 0;
	}

	m_x += m_diff_x;
	m_y += m_diff_y;

	if (!isOnFloor())
	{
		m_diff_y = 1;
		this->m_countHeight++;
	}
	else
	{
		m_diff_y = 0;
		checkFallHeight();
		m_countHeight = 0;
	}
}

void Mario::jump(Barrel b[], int barrelCurr)
{
	int counterFlag = 0;
	char curr = this->getMapChar();
	int jumpHeight = 2;
	m_diff_y = (int)gameConfig::Direction::NEGATIVE;
	for (int i = 0; i < jumpHeight; i++)
	{
		if (isNearWall(m_diff_x)) //mario movement
			m_diff_x = 0;
		if (isUnderFloor()) { //dont jump if theres floor exactly above me
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


		if (barrelCurr)                     //keep moving the barrels
			{
				for (int i = 0; i < barrelCurr; i++)
				{
					curr = b[i].getMapChar();
					b[i].draw(curr);
					b[i].move();
				}
		}

		for (int i = 0; i < barrelCurr; i++) //keep moving the barrels
		{
			curr = b[i].getMapChar();
			b[i].draw('O');
		}
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

void Mario::climb(Barrel arrB[], int barrelCurr)
{
	char curr;
	this->m_diff_y = (int)gameConfig::Direction::NEGATIVE;
	while (this->map->currentMap[m_y][m_x] == 'H')
	{
		this->draw('H'); //mario movemant
		if (barrelCurr)
		{
			for (int i = 0; i < barrelCurr; i++)    //barrel movemant
			{
				curr = arrB[i].getMapChar();
				arrB[i].draw(curr);
				arrB[i].move();
			}
		}
		
		
		m_y += m_diff_y;

		this->draw('#'); //mario movemant
		
		for (int i = 0; i < barrelCurr; i++) //barrel movemant
		{
			curr = arrB[i].getMapChar();
			arrB[i].draw('O');
		}
		Sleep(gameConfig::SLEEP_DURATION);
	}
    curr = this->getMapChar();
	this->draw(curr);
	
	if (barrelCurr)
	{
		for (int i = 0; i < barrelCurr; i++)    //barrel movemant
		{
			curr = arrB[i].getMapChar();
			arrB[i].draw(curr);
			arrB[i].move();
		}
	}

	m_y += m_diff_y;
	this->draw('#');
	for (int i = 0; i < barrelCurr; i++) //barrel movemant
	{
		curr = arrB[i].getMapChar();
		arrB[i].draw('O');
	}
	
	Sleep(gameConfig::SLEEP_DURATION);
	this->draw(' ');
}

void Mario::downLadder(Barrel arrB[], int barrelCurr)
{
	this->m_diff_y = (int)gameConfig::Direction::POSITIVE;
	while (this->map->currentMap[m_y + 2][m_x] == 'H') {
		char curr = this->getMapChar();
		this->draw(curr);
		if (barrelCurr)
		{
			for (int i = 0; i < barrelCurr; i++)    //barrel movemant
			{
				curr = arrB[i].getMapChar();
				arrB[i].draw(curr);
				arrB[i].move();
			}
		}

		m_y += m_diff_y;
		this->draw('#');
		
		for (int i = 0; i < barrelCurr; i++) //barrel movemant
		{
			curr = arrB[i].getMapChar();
			arrB[i].draw('O');
		}
		Sleep(gameConfig::SLEEP_DURATION);
	}
	char curr = this->getMapChar();
	this->draw(curr);
	if (barrelCurr)
	{
		for (int i = 0; i < barrelCurr; i++)    //barrel movemant
		{
			curr = arrB[i].getMapChar();
			arrB[i].draw(curr);
			arrB[i].move();
		}
	}
	m_y += m_diff_y;
	this->draw('#');
	
	for (int i = 0; i < barrelCurr; i++) //barrel movemant
	{
		curr = arrB[i].getMapChar();
		arrB[i].draw('O');
	}
	Sleep(gameConfig::SLEEP_DURATION);
}

void Mario::checkFallHeight()
{
	if (m_countHeight >= 5)
	{
		this->lives--;
		this->m_countHeight = 0;
	}
	
	
}

void Mario::resetMario()
{
	 m_x = (int)Map::GAME_WIDTH / 2; //start point in the middle of the floor
	 m_y = (int)Map::GAME_HEIGHT - 2;//start point one character above the floor
	 m_diff_x = 0;
	 m_diff_y = 0;
	 m_countHeight = 0;
	return;
}
