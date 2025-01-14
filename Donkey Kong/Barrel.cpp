#include "Barrel.h"
#include <Windows.h>
#include "Mario.h"
#include "Point.h"

int Barrel::barrelCurr = 0;

int Barrel::barrelSpawnCounter = 0;

void Barrel::move(std::vector<Barrel>& barrels,Mario* mario) {
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

    if (isExploded) {
        handleExplosion(barrels,mario);
    }
    else {
        updatePosition();
        
        draw('O'); // Replace 'O' with the character representing a barrel
        m_diff_x = m_prev_diff_x;
    }
}

void Barrel::updatePosition() {
    position.setX(position.getX() + m_diff_x);
    position.setY(position.getY() + m_diff_y);
}


void Barrel::handleExplosion(std::vector<Barrel>& barrels, Mario* mario) {
    draw('*');
    Sleep((int)gameConfig::Sleep::EXPLOSION_SLEEP);
    Point marioPos = { mario->getX(), mario->getY() };

    // Check if the explosion is near Mario
    if (isMarioNearMe(marioPos)) {
        mario->setIsNearExplosion(true);
    }
    draw(' '); // Clear the explosion
    // Remove this barrel from the vector
    auto it = std::find(barrels.begin(), barrels.end(), *this);
    if (it != barrels.end()) { barrels.erase(it); }
    Barrel::decrementBarrelCurr();
}


bool Barrel::isOnAir(char& refFloor) {
    // Check the floor one position below the current position
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
    this->position = startingPosition;
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

void Barrel::addBarrel(std::vector<Barrel>& barrels, Map* map) {
    barrels.push_back(Barrel(map, startingPosition)); // Add a new Barrel to the vector
}

