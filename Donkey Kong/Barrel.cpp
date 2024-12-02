#include "Barrel.h"

void Barrel::move()
{
	char floor = '\0';
	char& refFloor = floor;
	m_prev_diff_x = m_diff_x;
	if (isOnAir(refFloor))
	{
		m_diff_y = (int)gameConfig::Direction::POSITIVE;
		m_diff_x = 0;
	}
	else
	{
		m_diff_y = 0;
		switch (floor)
		{
		case  '>':
			m_diff_x = (int)gameConfig::Direction::POSITIVE;

			break;

		case '<':
			m_diff_x = (int)gameConfig::Direction::NEGATIVE;

			break;
			/*case 'H':
				m_diff_y = (int)gameConfig::Direction::POSITIVE;
				break;*/
		}




	}
	m_x += m_diff_x;
	m_y += m_diff_y;
	m_diff_x = m_prev_diff_x;
	return;
}

void Barrel::draw(char ch)
{
	gotoxy(m_x, m_y);
	this->map->currentMap[m_y][m_x] = ch;
	std::cout << ch;

}

bool Barrel::isOnAir(char& refFloor)
{
	refFloor = this->map->currentMap[m_y + 1][m_x];
	if (this->map->currentMap[m_y + 1][m_x] == ' ' || this->map->currentMap[m_y + 1][m_x] == 'H')
		return true;
	return false;
}

bool Barrel::isOnFloor(char& refFloor)
{
	refFloor = this->map->currentMap[m_y + 1][m_x];
	if (this->map->currentMap[m_y + 1][m_x] != ' ' && this->map->currentMap[m_y][m_x] != 'H')
		return true;
	return false;
}
