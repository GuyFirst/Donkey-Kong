//#include "Barrel.h"
//#include <Windows.h>
//#include "Mario.h"
//#include "Point.h"
//void Barrel::move(Mario* mario)
//{
//	char floor = '\0';
//	char& refFloor = floor;
//
//	// Erase barrel from the current position
//	draw(this->map->originalMap[position.getY()][position.getX()]); // Draw the background character at the current position
//	bool isExploded = false;
//	if (isOnAir(refFloor))
//	{
//		m_diff_y = (int)gameConfig::Direction::POSITIVE;
//		m_diff_x = 0;
//		m_fallCounter++;
//	}
//	else
//	{
//		m_diff_y = 0;
//		switch (floor)
//		{
//		case  '>':
//			m_prev_diff_x = m_diff_x = (int)gameConfig::Direction::POSITIVE;
//
//			break;
//
//		case '<':
//			m_prev_diff_x = m_diff_x = (int)gameConfig::Direction::NEGATIVE;
//
//			break;
//		}
//		isExploded = checkFallHeight();
//		m_fallCounter = 0;
//
//
//
//	}
//	if (isNearWall(m_diff_x))
//	{
//		reset();
//		return;
//	}
//	position.setX(position.getX() + m_diff_x);
//	position.setY(position.getY() + m_diff_y);
//	
//	// Draw barrel at the new position
//	if (isExploded) {
//		draw('*');  
//		Sleep((int)gameConfig::Sleep::EXPLOSION_SLEEP);
//		Point marioPos = { (*mario).getX(), (*mario).getY() };
//		if (isMarioNearMe(marioPos)) 
//			mario->setIsNearExplosion(true);
//		draw(' ');
//		reset();
//
//	}
//	else {
//		draw('O'); // Replace 'O' with the character representing a barrel
//	m_diff_x = m_prev_diff_x;
//}
//	return;
//}
//
//void Barrel::draw(char ch)
//{
//	gotoxy(position.getX(), position.getY());
//	
//	std::cout << ch;
//	map->currentMap[position.getY()][position.getX()] = ch;
//}
//
//bool Barrel::isOnAir(char& refFloor)
//{
//	refFloor = this->map->currentMap[position.getY() + 1][position.getX()];
//	if (this->map->currentMap[position.getY() + 1][position.getX()] == ' ' || this->map->currentMap[position.getY() + 1][position.getX()] == 'H')
//		return true;
//	return false;
//}
//
//bool Barrel::isNearWall(int dirX)
//{
//	if (dirX == (int)gameConfig::Direction::POSITIVE)
//	{
//		if (this->position.getX() > gameConfig::GAME_WIDTH - 4)
//			return true;
//	}
//	else
//	{
//		if (this->position.getX() <= 0)
//			return true;
//	}
//	return false;
//}
//
//void Barrel::reset()
//{
//	this->position.setX((int)gameConfig::Pos::BARREL_X_START);
//	this->position.setY((int)gameConfig::Pos::BARREL_Y_START);
//    m_diff_x = 0;
//	m_diff_y = 1;
//	m_prev_diff_x = 0;
//	return;
//}
//
////bool Barrel::isMarioNearMe(Point marioPos)
////{
////	Point currPosition(this->position.getX()-2,this->position.getY()-2);                //   the function checking if mario is near radius of 2 spaces within the boom
////	for (int col = 0; col < 5; col++) {  		                                        //
////		for (int row = 0; row < 5; row++)                                               //
////		{
////			if (marioPos == currPosition)
////				return true;
////			currPosition.setX(currPosition.getX() + 1);
////		}
////		currPosition.setY(currPosition.getY() + 1);
////		currPosition.setX(this->position.getX() - 2);
////	}
////	return false;
////}
//bool Barrel::isMarioNearMe(Point marioPos)
//{
//	// Define the radius for checking around the barrel
//	const int radius = 2;
//
//	// Loop through a 5x5 grid centered around the barrel's current position
//	for (int yOffset = -radius; yOffset <= radius; ++yOffset) {
//		for (int xOffset = -radius; xOffset <= radius; ++xOffset) {
//			
//			Point currPosition(this->position.getX() + xOffset, this->position.getY() + yOffset);
//
//			if (marioPos == currPosition) {
//				return true; // Mario is within the 5x5 area
//			}
//		}
//	}
//	return false; 
//}
//
//
//bool Barrel::isOnFloor(char& refFloor)
//{
//	refFloor = this->map->currentMap[this->position.getY() + 1][this->position.getX()];
//	if (this->map->currentMap[this->position.getY() + 1][this->position.getX()] != ' ' && this->map->currentMap[this->position.getY()][this->position.getX()] != 'H')
//		return true;
//	return false;
//}
//
//void Barrel::addBarrel(Barrel arr[], int size)
//{
//	Barrel b;
//	arr[size] = b;
//}
//
//bool Barrel::checkFallHeight()
//{
//	if (m_fallCounter >= 4)
//	{
//		this->m_fallCounter= 0;
//		return true;
//	}
//	return false;
//
//}
//
#include "Barrel.h"
#include <Windows.h>
#include "Mario.h"
#include "Point.h"

void Barrel::move(Mario* mario) {
    char floor = '\0';
    char& refFloor = floor;

    // Erase barrel from the current position
    draw(this->map->originalMap[position.getY()][position.getX()]);

    bool isExploded = false;
    if (isOnAir(refFloor)) {
        m_diff_y = (int)gameConfig::Direction::POSITIVE;
        m_diff_x = 0;
        m_fallCounter++;
    }
    else {
        m_diff_y = 0;
        switch (floor) {
        case '>':
            m_prev_diff_x = m_diff_x = (int)gameConfig::Direction::POSITIVE;
            break;
        case '<':
            m_prev_diff_x = m_diff_x = (int)gameConfig::Direction::NEGATIVE;
            break;
        }
        isExploded = checkFallHeight();
        m_fallCounter = 0;
    }

    if (isNearWall(m_diff_x)) {
        reset();
        return;
    }

    updatePosition();

    // Draw barrel at the new position
    if (isExploded) {
        handleExplosion(mario);
    }
    else {
        draw('O'); // Replace 'O' with the character representing a barrel
        m_diff_x = m_prev_diff_x;
    }
}

void Barrel::updatePosition() {
    position.setX(position.getX() + m_diff_x);
    position.setY(position.getY() + m_diff_y);
}

void Barrel::handleExplosion(Mario* mario) {
    draw('*');
    Sleep((int)gameConfig::Sleep::EXPLOSION_SLEEP);
    Point marioPos = { mario->getX(), mario->getY() };
    if (isMarioNearMe(marioPos)) {
        mario->setIsNearExplosion(true);
    }
    draw(' ');
    reset();
}

void Barrel::draw(char ch) const {
    gotoxy(position.getX(), position.getY());
    std::cout << ch;
    map->currentMap[position.getY()][position.getX()] = ch;
}

bool Barrel::isOnAir(char& refFloor) {
    refFloor = this->map->currentMap[position.getY() + 1][position.getX()];
    return refFloor == ' ' || refFloor == 'H';
}

bool Barrel::isNearWall(int dirX) const {
    if (dirX == (int)gameConfig::Direction::POSITIVE) 
        return this->position.getX() > gameConfig::GAME_WIDTH - 4;
    else 
        return this->position.getX() <= 0;
}

void Barrel::reset() {
    this->position.setX((int)gameConfig::Pos::BARREL_X_START);
    this->position.setY((int)gameConfig::Pos::BARREL_Y_START);
    m_diff_x = 0;
    m_diff_y = 1;
    m_prev_diff_x = 0;
}

bool Barrel::isMarioNearMe(Point marioPos) const {
    const int radius = 2;
    for (int yOffset = -radius; yOffset <= radius; ++yOffset) {
        for (int xOffset = -radius; xOffset <= radius; ++xOffset) {
            Point currPosition(this->position.getX() + xOffset, this->position.getY() + yOffset);
            if (marioPos == currPosition) {
                return true;
            }
        }
    }
    return false;
}

bool Barrel::checkFallHeight() {
    if (m_fallCounter >= 4) {
        m_fallCounter = 0;
        return true;
    }
    return false;
}

void Barrel::addBarrel(Barrel arr[], int size) {
    Barrel b;
    arr[size] = b;
}

