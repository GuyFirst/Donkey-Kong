#include "Barrel.h"
#include <Windows.h>
#include "Mario.h"
#include "Point.h"
void Barrel::move(Mario* mario)
{
	char floor = '\0';
	char& refFloor = floor;

	// Erase barrel from the current position
	draw(this->map->originalMap[m_y][m_x]); // Draw the background character at the current position
	bool isExploded = false;
	if (isOnAir(refFloor))
	{
		m_diff_y = (int)gameConfig::Direction::POSITIVE;
		m_diff_x = 0;
		m_fallCounter++;
	}
	else
	{
		m_diff_y = 0;
		switch (floor)
		{
		case  '>':
			m_prev_diff_x = m_diff_x = (int)gameConfig::Direction::POSITIVE;

			break;

		case '<':
			m_prev_diff_x = m_diff_x = (int)gameConfig::Direction::NEGATIVE;

			break;
		}
		isExploded = checkFallHeight();
		m_fallCounter = 0;



	}
	if (isNearWall(m_diff_x))
	{
		reset();
		return;
	}
	m_x += m_diff_x;
	m_y += m_diff_y;
	// Draw barrel at the new position
	if (isExploded) {
		draw('*');                                                              // fix the issue when we still be seeing the explosion
		Point marioPos = { (*mario).getX(), (*mario).getY() };
		if (isMarioNearMe(marioPos)) //LEMAMESHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
		{
			(*mario).m_isNearExplosion = true;
		}
		reset();
	}
	else {
		draw('O'); // Replace 'O' with the character representing a barrel
	m_diff_x = m_prev_diff_x;
}
	return;
}

void Barrel::draw(char ch)
{
	gotoxy(m_x, m_y);
	
	std::cout << ch;
	map->currentMap[m_y][m_x] = ch;
}

bool Barrel::isOnAir(char& refFloor)
{
	refFloor = this->map->currentMap[m_y + 1][m_x];
	if (this->map->currentMap[m_y + 1][m_x] == ' ' || this->map->currentMap[m_y + 1][m_x] == 'H')
		return true;
	return false;
}

bool Barrel::isNearWall(int dirX)
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

void Barrel::reset()
{
    m_x = 5; //first apperance of any barrel
	m_y = 4;
    m_diff_x = 0;
	m_diff_y = 1;
	m_prev_diff_x = 0;
	return;
}

bool Barrel::isOnFloor(char& refFloor)
{
	refFloor = this->map->currentMap[m_y + 1][m_x];
	if (this->map->currentMap[m_y + 1][m_x] != ' ' && this->map->currentMap[m_y][m_x] != 'H')
		return true;
	return false;
}

void Barrel::addBarrel(Barrel arr[], int size)
{
	Barrel b;
	arr[size] = b;
}

bool Barrel::checkFallHeight()
{
	if (m_fallCounter >= 4)
	{
		this->m_fallCounter= 0;
		return true;
	}
	return false;

}

