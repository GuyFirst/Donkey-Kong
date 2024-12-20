﻿
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

    handleInput(key);

    executeStateAction();

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
			if (isOnFloor()) {
				setState(State::STANDING, 0, 0);
			}
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



void Mario::handleCeilingCollision() {
    m_diff_y = (int)gameConfig::Direction::POSITIVE; // Begin falling
    position.setY(position.getY() + m_diff_y);

    // Update state to WALKING or STANDING depending on horizontal movement
    if (m_diff_x != 0 && !isNearWall(m_diff_x)) 
        state = State::WALKING;
    
    else 
        state = State::STANDING;

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
    m_diff_x = m_diff_y = m_countHeight = m_isNearExplosion = 0;
}

bool Mario::isBarrelHere() const         { return this->map->currentMap[position.getY()][position.getX()] == 'O'; }

bool Mario::isObstacleAbove(int x) const { return this->map->currentMap[position.getY() - 1][x] != ' ' && this->map->currentMap[position.getY() - 1][x] != 'H'; }

bool Mario::isNearPaulina() const        { return this->map->currentMap[position.getY()][position.getX() + m_diff_x] == '$'; }

char Mario::getMapChar() const           { return this->map->originalMap[position.getY()][position.getX()]; }

bool Mario::isOnFloor() const            { return this->map->currentMap[position.getY() + 1][position.getX()] != ' ' && this->map->currentMap[position.getY() + 1][position.getX()] != 'O'; }


bool Mario::isUnderLadder() const        { return this->map->currentMap[position.getY() - 1][position.getX()] == 'H' ||
                                                  this->map->currentMap[position.getY()][position.getX()] == 'H'     ||
                                                  this->map->currentMap[position.getY() + 1][position.getX()] == 'H';   }

bool Mario::isOnLadder() const           { return this->map->currentMap[position.getY() + 2][position.getX()] == 'H' ||
                                                  this->map->currentMap[position.getY() + 1][position.getX()] == 'H';      }

bool Mario::isCeilingAbove() const       { return this->map->currentMap[position.getY() - 1][position.getX()] != ' ' &&
                                                  this->map->currentMap[position.getY() - 1][position.getX()] != 'H';
}

bool Mario::isUnderFloor() const {
    if (state == State::STANDING) 
        return this->map->currentMap[position.getY() - 1][position.getX()] != ' ' &&
               this->map->currentMap[position.getY() - 1][position.getX()] != 'H' ;  

    else 
        return isUnderFloorWhileMoving(); 
}



bool Mario::isUnderFloorWhileMoving() const {
    if (m_diff_x == (int)gameConfig::Direction::POSITIVE)                                // going right
        return isObstacleAbove(position.getX()) || isObstacleAbove(position.getX() + 1);
    else if (m_diff_x == (int)gameConfig::Direction::NEGATIVE)                           // going left
        return isObstacleAbove(position.getX()) || isObstacleAbove(position.getX() - 1);
    
    return false;
}



bool Mario::isNearWall(int dirX) const {
    if (dirX == (int)gameConfig::Direction::POSITIVE) 
         return position.getX() > gameConfig::GAME_WIDTH - 4;
    
    else 
         return position.getX() <= 0; 
}
