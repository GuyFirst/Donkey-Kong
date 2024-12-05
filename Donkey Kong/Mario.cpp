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


void Mario::move(gameConfig::eKeys key )
{
	// Erase Mario from the current position
	draw(this->map->currentMap[m_y][m_x]); // Draw the background character at the current position


	// If no key is provided, continue the last action
	if (key != gameConfig::eKeys::NONE) {
		switch (key) {
		case gameConfig::eKeys::LEFT:
			state = State::WALKING;
			m_diff_x = (int)gameConfig::Direction::NEGATIVE;
			m_diff_y = 0;
			break;

		case gameConfig::eKeys::RIGHT:
			state = State::WALKING;
			m_diff_x = (int)gameConfig::Direction::POSITIVE;
			m_diff_y = 0;
			break;

		case gameConfig::eKeys::UP:
			if (isUnderLadder()) {
				state = State::CLIMBING_UP;
			}
			else if (isOnFloor()) {
				state = State::JUMPING;
			}
			break;

		case gameConfig::eKeys::DOWN:
			if (isOnLadder()) {
				state = State::CLIMBING_DOWN;
			}
			m_diff_y = (int)gameConfig::Direction::POSITIVE;
			break;

		case gameConfig::eKeys::STAY:
			state = State::STANDING;
			m_diff_x = 0;
			m_diff_y = 0;
			return;
		}
	}

	// Execute the current action based on the state
	switch (state) {
	case State::JUMPING:
		jump(); 
		break;

	case State::CLIMBING_UP:
		climb(); 
		break;

	case State::CLIMBING_DOWN:
		downLadder(); 
		break;

	case State::WALKING:
		m_x += m_diff_x; 
		m_y += m_diff_y; 
		break;

	case State::STANDING:
		break; 
	}

	// Handle falling if not on the floor
	if (!isOnFloor()) {
		m_diff_y = 1; 
		m_countHeight++;
	}
	else {
		m_diff_y = 0; // Reset vertical movement
		checkFallHeight(); // Check for fall damage
		m_countHeight = 0;
	}

	// Draw Mario at the new position
	draw('@');
}


void Mario::jump()
{
	
	m_x += m_diff_x;

	// When Mario is on the floor
	if (state == State::JUMPING && isOnFloor()) {
		m_diff_y = -2; 
		m_y += m_diff_y;
		state = State::JUMPING;
		return;
	}

	// When Mario is in the air
	if (state == State::JUMPING && !isOnFloor()) {
		m_diff_y = 2;
		m_y += m_diff_y;

		// Check if he landed back on the floor
		if (isOnFloor()) {
			// Return to WALKING state if there is horizontal movement
			if (m_diff_x != 0 && !isNearWall(m_diff_x)) {
				state = State::WALKING;
			}
			else {
				state = State::STANDING; // Stop if not moving horizontally
			}
			m_diff_y = 0; 
		}
		return;
	}
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
	if (this->map->currentMap[m_y - 1][m_x] != ' ' &&  this->map->currentMap[m_y - 2][m_x] != ' ')
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
	if (this->map->currentMap[m_y - 1][m_x] == 'H' || this->map->currentMap[m_y][m_x] == 'H' || this->map->currentMap[m_y + 1][m_x] == 'H')
		return true;
	return false;
}

bool Mario::isOnLadder()
{
	if (this->map->currentMap[m_y + 2][m_x] == 'H' ||  this->map->currentMap[m_y + 1][m_x] == 'H')
		return true;
	return false;
}

void Mario::climb()
{
	if (isUnderLadder()) {
		m_diff_y = (int)gameConfig::Direction::NEGATIVE; 
		m_y += m_diff_y; 
		state = State::CLIMBING_UP; 
	}

	// If mario done climbing
	if (!isUnderLadder()) {
		state = State::STANDING; 
		m_diff_y = 0; 
	}
}

void Mario::downLadder()
{
	if (isOnLadder()) {
		m_diff_y = (int)gameConfig::Direction::POSITIVE; 
		m_y += m_diff_y; 
		state = State::CLIMBING_DOWN; 
	}

	// If he isn't on the ladder
	if (!isOnLadder()) {
		state = State::STANDING; 
		m_diff_y = 0; 
	}
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



