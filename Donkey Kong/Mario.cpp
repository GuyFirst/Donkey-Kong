//#include <iostream>
//#include <Windows.h>
//
//#include "Mario.h"
//#include "gameConfig.h"
//#include "general.h"
//
//
//void Mario::draw(char ch) const
//{
//	gotoxy(position.getX(), position.getY());
//	std::cout << ch;
//}
//
//
//
//void Mario::move(gameConfig::eKeys key) {
//	// Erase Mario from the current position
//	if (m_isNearExplosion || isBarrelHere())
//	{
//		lives--;
//		Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
//		return;
//	}
//
//	draw(this->map->currentMap[position.getY()][position.getX()]);
//
//	// Handle input keys
//	if (key != gameConfig::eKeys::NONE) {
//		switch (key) {
//		case gameConfig::eKeys::LEFT:
//			state = State::WALKING;
//			m_diff_x = (int)gameConfig::Direction::NEGATIVE;
//			m_diff_y = 0;
//			break;
//
//		case gameConfig::eKeys::RIGHT:
//			state = State::WALKING;
//			m_diff_x = (int)gameConfig::Direction::POSITIVE;
//			m_diff_y = 0;
//			break;
//
//		case gameConfig::eKeys::UP:
//			if (isUnderFloor()) {
//				break;
//			}
//			else if (isUnderLadder()) {
//				state = State::CLIMBING_UP;
//			}
//			else if (isOnFloor()) {
//				state = State::JUMPING;
//			}
//			break;
//
//		case gameConfig::eKeys::DOWN:
//			if (isOnLadder()) {
//				state = State::CLIMBING_DOWN;
//			}
//			if (!isOnFloor()) {
//				m_diff_y = (int)gameConfig::Direction::POSITIVE;
//			}
//			break;
//
//		case gameConfig::eKeys::STAY:
//			state = State::STANDING;
//			m_diff_x = 0;
//			m_diff_y = 0;
//			return;
//		}
//	}
//
//	// Execute the current action based on the state
//	switch (state) {
//	case State::JUMPING:
//		jump();
//		break;
//
//	case State::CLIMBING_UP:
//		climb();
//		break;
//
//	case State::CLIMBING_DOWN:
//		downLadder();
//		break;
//
//	case State::WALKING:
//		if (isNearWall(this->m_diff_x)) {
//			m_diff_x = 0; // Stop horizontal movement
//			if (isOnFloor()) {
//				state = State::STANDING; // Reset to STANDING if on the floor
//			}
//		}
//		position.setX(position.getX() + m_diff_x);
//	    position.setY(position.getY() + m_diff_y);
//		break;
//
//	case State::STANDING:
//		break;
//	}
//
//		// Handle falling if not on the floor
//		if (!isOnFloor()) {
//			m_diff_y = 1; // Simulate gravity
//			m_countHeight++;
//		}
//		else {
//			m_diff_y = 0; // Reset vertical movement
//			checkFallHeight(); // Check for fall damage
//			m_countHeight = 0;
//		}
//	
//	// Draw Mario at the new position
//	draw('@');
//}
//
//
//
//
//void Mario::jump() {
//	// Add horizontal movement during the jump
//	if (!isNearWall(m_diff_x)) {
//		position.setX(position.getX() + m_diff_x);
//	}
//	else {
//		// If Mario hits a wall, stop horizontal movement
//		m_diff_x = 0;
//	}
//
//	// Check for collision with a ceiling
//	if (this->map->currentMap[position.getY() - 1][position.getX()] != ' ' && this->map->currentMap[position.getY() - 1][position.getX()] != 'H') {
//		// If there is a ceiling, stop upward movement and fall
//		m_diff_y = 1; // Begin falling
//		position.setY(position.getY() + m_diff_y);
//
//		// Update state to WALKING or STANDING depending on horizontal movement
//		if (m_diff_x != 0 && !isNearWall(m_diff_x)) {
//			state = State::WALKING;
//		}
//		else {
//			state = State::STANDING;
//		}
//
//		this->jumpCounter = 0; // Reset jump counter
//		return;
//	}
//
//	// Handle upward movement during the jump
//	if (this->jumpCounter < 2) {
//		m_diff_y = -1; // Move up
//		position.setY(position.getY() + m_diff_y);
//		state = State::JUMPING;
//		this->jumpCounter++;
//		return;
//	}
//
//	// Handle downward movement if in the air
//	if (state == State::JUMPING && !isOnFloor()) {
//		m_diff_y = 1; // Move down
//		position.setY(position.getY() + m_diff_y);
//
//		// Check if Mario has landed on the floor
//		if (isOnFloor()) {
//			// Update state to WALKING or STANDING depending on horizontal movement
//			if (m_diff_x != 0 && !isNearWall(m_diff_x)) {
//				state = State::WALKING;
//			}
//			else {
//				state = State::STANDING;
//			}
//			m_diff_y = 0; // Reset vertical movement
//			this->jumpCounter = 0; // Reset jump counter
//		}
//
//		return;
//	}
//	
//	// If mario landed on upper floor after the jump
//	else  {
//		state = State::WALKING;
//		m_diff_y = 0; // Reset vertical movement
//		this->jumpCounter = 0; // Reset jump counter
//	}
//}
//
//
//
//
//
//bool Mario::isNearWall(int dirX)
//{
//	if (dirX == (int)gameConfig::Direction::POSITIVE)
//	{
//		if (position.getX() > gameConfig::GAME_WIDTH - 4)
//			return true;
//	}
//	else
//	{
//		if (position.getX() <= 0)
//			return true;
//	}
//	return false;
//
//}
//
//bool Mario::isOnFloor()
//{
//	if (this->map->currentMap[position.getY() + 1][position.getX()] != ' ')
//		return true;
//	return false;
//}
//
//bool Mario::isUnderFloor()
//{
//	if (state == State::STANDING) {
//		if (this->map->currentMap[position.getY() - 1][position.getX()] != ' ' && this->map->currentMap[position.getY() - 1][position.getX()] != 'H')
//			return true;
//	}
//	else {
//		if (this->m_diff_x == (int)gameConfig::Direction::POSITIVE) // going right
//			if ((this->map->currentMap[position.getY() - 1][position.getX()] != ' ' && this->map->currentMap[position.getY() - 1][position.getX()] != 'H') || ((this->map->currentMap[position.getY() - 1][position.getX() + 1] != ' ' && this->map->currentMap[position.getY() - 1][position.getX() +1] != 'H')))
//				return true;
//		if(this->m_diff_x == (int)gameConfig::Direction::NEGATIVE) // going left
//		if ((this->map->currentMap[position.getY() - 1][position.getX()] != ' ' && this->map->currentMap[position.getY() - 1][position.getX()] != 'H') || ((this->map->currentMap[position.getY() - 1][position.getX() - 1] != ' ' && this->map->currentMap[position.getY() - 1][position.getX() - 1] != 'H')))
//			return true;
//	}
//	return false;
//}
//
//bool Mario::isNearPaulina()
//{
//	if (this->map->currentMap[position.getY()][position.getX() + m_diff_x] == '$')
//		return true;
//	return false;
//}
//
//char Mario::getMapChar()
//{
//	return this->map->originalMap[position.getY()][position.getX()];
//}
//
//bool Mario::isUnderLadder()
//{
//	if (this->map->currentMap[position.getY() - 1][position.getX()] == 'H' || this->map->currentMap[position.getY()][position.getX()] == 'H' || this->map->currentMap[position.getY() + 1][position.getX()] == 'H')
//		return true;
//	return false;
//}
//
//bool Mario::isOnLadder()
//{
//	if (this->map->currentMap[position.getY() + 2][position.getX()] == 'H' ||  this->map->currentMap[position.getY() + 1][position.getX()] == 'H')
//		return true;
//	return false;
//}
//
//void Mario::climb()
//{
//	if (isUnderLadder()) {
//		m_diff_y = (int)gameConfig::Direction::NEGATIVE; 
//		position.setY(position.getY() + m_diff_y);
//		state = State::CLIMBING_UP; 
//	}
//
//	// If mario done climbing
//	if (!isUnderLadder()) {
//		state = State::STANDING; 
//		m_diff_y = 0; 
//	}
//}
//
//void Mario::downLadder()
//{
//	if (isOnLadder()) {
//		m_diff_y = (int)gameConfig::Direction::POSITIVE; 
//		position.setY(position.getY() + m_diff_y);
//		state = State::CLIMBING_DOWN; 
//	}
//
//	// If he isn't on the ladder
//	if (!isOnLadder()) {
//		state = State::STANDING; 
//		m_diff_y = 0; 
//	}
//}
//
//void Mario::checkFallHeight()
//{
//	if (m_countHeight >= 5)
//	{
//		this->lives--;
//		this->m_countHeight = 0;
//	}
//	
//	
//}
//
//void Mario::resetMario()
//{
//
//	 position.setX((int)Map::GAME_WIDTH / 2); //start point in the middle of the floor
//	 position.setY((int)Map::GAME_HEIGHT - 2);//start point one character above the floor
//	 m_isNearExplosion = false;
//	 m_diff_x = 0;
//	 m_diff_y = 0;
//	 m_countHeight = 0;
//	return;
//}
//
//bool Mario::isBarrelHere()
//{
//	if (this->map->currentMap[position.getY()][position.getX()] == 'O')
//		return true;
//	return false;
//}
//
//
//
//
// Mario.cpp
#include <iostream>
#include <Windows.h>
#include "Mario.h"
#include "gameConfig.h"
#include "general.h"

void Mario::draw(char ch) const {
    gotoxy(position.getX(), position.getY());
    std::cout << ch;
}

void Mario::move(gameConfig::eKeys key) {
    // Erase Mario from the current position
    draw(this->map->currentMap[position.getY()][position.getX()]);

    // Check for collision with barrels before moving
    if (checkForCollisions()) {
        return;
    }

    // Handle input keys
    handleInput(key);

    // Execute the current action based on the state
    executeStateAction();

    // Handle falling if not on the floor
    handleFalling();
    
    // Check for collision with barrels after moving
    if (checkForCollisions()) {
        return;
    }

    // Draw Mario at the new position
    draw('@');
}


bool Mario::checkForCollisions() {
    if (m_isNearExplosion || isBarrelHere()) {
        lives--;
        Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
        resetMario();
        return true;
    }
    return false;
}


void Mario::handleInput(gameConfig::eKeys key) {
    if (key != gameConfig::eKeys::NONE) {
        switch (key) {
        case gameConfig::eKeys::LEFT:
            setState(State::WALKING, (int)gameConfig::Direction::NEGATIVE, 0);
            break;
        case gameConfig::eKeys::RIGHT:
            setState(State::WALKING, (int)gameConfig::Direction::POSITIVE, 0);
            break;
        case gameConfig::eKeys::UP:
            handleUpKey();
            break;
        case gameConfig::eKeys::DOWN:
            handleDownKey();
            break;
        case gameConfig::eKeys::STAY:
            setState(State::STANDING, 0, 0);
            return;
        }
    }
}

void Mario::handleUpKey() {
    if (isUnderFloor()) {
        return;
    }
    else if (isUnderLadder()) {
        state = State::CLIMBING_UP;
    }
    else if (isOnFloor()) {
        state = State::JUMPING;
    }
}

void Mario::handleDownKey() {
    if (isOnLadder()) {
        state = State::CLIMBING_DOWN;
    }
    if (!isOnFloor()) {
        m_diff_y = (int)gameConfig::Direction::POSITIVE;
    }
}

void Mario::setState(State newState, int diffX, int diffY) {
    state = newState;
    m_diff_x = diffX;
    m_diff_y = diffY;
}

void Mario::executeStateAction() {
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
        walk();
        break;
    case State::STANDING:
        break;
    }
}

void Mario::walk() {
    if (isNearWall(m_diff_x)) {
        m_diff_x = 0; // Stop horizontal movement
        if (isOnFloor()) {
            state = State::STANDING; // Reset to STANDING if on the floor
        }
    }
    position.setX(position.getX() + m_diff_x);
    position.setY(position.getY() + m_diff_y);
}

void Mario::handleFalling() {
    if (!isOnFloor()) {
        m_diff_y = 1; // Simulate gravity
        m_countHeight++;
    }
    else {
        m_diff_y = 0; // Reset vertical movement
        checkFallHeight(); // Check for fall damage
        m_countHeight = 0;
    }
}

void Mario::jump() {
    // Add horizontal movement during the jump
    if (!isNearWall(m_diff_x)) {
        position.setX(position.getX() + m_diff_x);
    }
    else {
        m_diff_x = 0; // Stop horizontal movement
    }

    // Check for collision with a ceiling
    if (isCeilingAbove()) {
        handleCeilingCollision();
        return;
    }

    // Handle upward movement during the jump
    if (jumpCounter < 2) {
        m_diff_y = -1; // Move up
        position.setY(position.getY() + m_diff_y);
        state = State::JUMPING;
        jumpCounter++;
        return;
    }

    // Handle downward movement if in the air
    if (state == State::JUMPING && !isOnFloor()) {
        m_diff_y = 1; // Move down
        position.setY(position.getY() + m_diff_y);
        handleLanding();
        return;
    }

    // If Mario landed on upper floor after the jump
    state = State::WALKING;
    m_diff_y = 0; // Reset vertical movement
    jumpCounter = 0; // Reset jump counter
}

bool Mario::isCeilingAbove() const {
    return this->map->currentMap[position.getY() - 1][position.getX()] != ' ' &&
        this->map->currentMap[position.getY() - 1][position.getX()] != 'H';
}

void Mario::handleCeilingCollision() {
    m_diff_y = 1; // Begin falling
    position.setY(position.getY() + m_diff_y);

    // Update state to WALKING or STANDING depending on horizontal movement
    if (m_diff_x != 0 && !isNearWall(m_diff_x)) {
        state = State::WALKING;
    }
    else {
        state = State::STANDING;
    }

    jumpCounter = 0; // Reset jump counter
}

void Mario::handleLanding() {
    if (isOnFloor()) {
        // Update state to WALKING or STANDING depending on horizontal movement
        if (m_diff_x != 0 && !isNearWall(m_diff_x)) {
            state = State::WALKING;
        }
        else {
            state = State::STANDING;
        }
        m_diff_y = 0; // Reset vertical movement
        jumpCounter = 0; // Reset jump counter
    }
}

bool Mario::isNearWall(int dirX) const {
    if (dirX == (int)gameConfig::Direction::POSITIVE) {
        return position.getX() > gameConfig::GAME_WIDTH - 4;
    }
    else {
        return position.getX() <= 0;
    }
}

bool Mario::isOnFloor() const {
    return this->map->currentMap[position.getY() + 1][position.getX()] != ' ';
}

bool Mario::isUnderFloor() const {
    if (state == State::STANDING) {
        return this->map->currentMap[position.getY() - 1][position.getX()] != ' ' &&
            this->map->currentMap[position.getY() - 1][position.getX()] != 'H';
    }
    else {
        return isUnderFloorWhileMoving();
    }
}

bool Mario::isUnderFloorWhileMoving() const {
    if (m_diff_x == (int)gameConfig::Direction::POSITIVE) { // going right
        return isObstacleAbove(position.getX()) || isObstacleAbove(position.getX() + 1);
    }
    else if (m_diff_x == (int)gameConfig::Direction::NEGATIVE) { // going left
        return isObstacleAbove(position.getX()) || isObstacleAbove(position.getX() - 1);
    }
    return false;
}

bool Mario::isObstacleAbove(int x) const {
    return this->map->currentMap[position.getY() - 1][x] != ' ' &&
        this->map->currentMap[position.getY() - 1][x] != 'H';
}

bool Mario::isNearPaulina() const {
    return this->map->currentMap[position.getY()][position.getX() + m_diff_x] == '$';
}

char Mario::getMapChar() const {
    return this->map->originalMap[position.getY()][position.getX()];
}

bool Mario::isUnderLadder() const {
    return this->map->currentMap[position.getY() - 1][position.getX()] == 'H' ||
        this->map->currentMap[position.getY()][position.getX()] == 'H' ||
        this->map->currentMap[position.getY() + 1][position.getX()] == 'H';
}

bool Mario::isOnLadder() const {
    return this->map->currentMap[position.getY() + 2][position.getX()] == 'H' ||
        this->map->currentMap[position.getY() + 1][position.getX()] == 'H';
}

void Mario::climb() {
    if (isUnderLadder()) {
        m_diff_y = (int)gameConfig::Direction::NEGATIVE;
        position.setY(position.getY() + m_diff_y);
        state = State::CLIMBING_UP;
    }

    // If Mario is done climbing
    if (!isUnderLadder()) {
        state = State::STANDING;
        m_diff_y = 0;
    }
}

void Mario::downLadder() {
    if (isOnLadder()) {
        m_diff_y = (int)gameConfig::Direction::POSITIVE;
        position.setY(position.getY() + m_diff_y);
        state = State::CLIMBING_DOWN;
    }

    // If he isn't on the ladder
    if (!isOnLadder()) {
        state = State::STANDING;
        m_diff_y = 0;
    }
}

void Mario::checkFallHeight() {
    if (m_countHeight >= 5) {
        lives--;
        m_countHeight = 0;
    }
}

void Mario::resetMario() {
    position.setX((int)Map::GAME_WIDTH / 2); // start point in the middle of the floor
    position.setY((int)Map::GAME_HEIGHT - 2); // start point one character above the floor
    m_isNearExplosion = false;
    m_diff_x = 0;
    m_diff_y = 0;
    m_countHeight = 0;
}

bool Mario::isBarrelHere() const {
    return this->map->currentMap[position.getY()][position.getX()] == 'O';
}

