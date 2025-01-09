#include "Ghost.h"
#include <cstdlib> // std::rand
#include <ctime>   // std::time
#include <iostream>
#include <vector>
#include "general.h"
#include "gameConfig.h"

void Ghost::draw(char ch) const {
    gotoxy(position.getX(), position.getY());
    std::cout << ch;
    //bug of disappearing P 
    map->currentMap[position.getY()][position.getX()] = ch;
}

void Ghost::move(std::vector<Ghost>& ghosts) {
    
    draw(map->originalMap[position.getY()][position.getX()]);

    // Handle potential collisions or direction changes
    handleCollision(ghosts);
    handleDirectionChange();

    // Update position 
    position.setX(position.getX() + m_diff_x);

    // Draw ghost at the new position
    draw('x');
}

void Ghost::handleCollision(std::vector<Ghost>& ghosts) {
    for (auto& other : ghosts) {
        // Skip checking collision with itself
        if (&other == this) {
            continue;
        }

        // Check if two ghosts are on the same row and are facing each other
        if (this->position.getY() == other.position.getY()) {
            
            if (this->isNearOtherGhosts(ghosts)) {
                
                this->m_diff_x = -this->m_diff_x;
                other.m_diff_x = -other.m_diff_x;
            }
        }
    }

    // Handle boundary collision 
    if (isNearBoundary()) {  m_diff_x = -m_diff_x; }
}



void Ghost::handleDirectionChange() {
    int random = ((std::rand() + m_id) % 100) + 1; // number between 1 and 100

    if (random <= 5 || !isOnFloor()) {  m_diff_x = -m_diff_x; }
}




bool Ghost::isNearBoundary() const  { 
    return (position.getX() <= 0 || position.getX() >= gameConfig::GAME_WIDTH - 2 || position.getX()+1 == 'Q' || position.getX() - 1 == 'Q');
}

bool Ghost::isNearOtherGhosts(const std::vector<Ghost>& ghosts) const {
    for (const auto& other : ghosts) {
        // Skip checking collision with itself
        if (&other == this) {
            continue;
        }

        // Check if the other ghost is adjacent (left, right)
        int diffX = abs(other.position.getX() - this->position.getX());
        int diffY = abs(other.position.getY() - this->position.getY());
        if ((diffX == 1 && diffY == 0)) {
            return true; 
        }
    }
    return false; 
}
void Ghost::reset() { position = startingPosition;}

bool Ghost::isOnFloor() const  { return this->map->currentMap[position.getY() + 1][position.getX()+m_diff_x] != ' ' && this->map->currentMap[position.getY() + 1][position.getX()+m_diff_x] != 'O'; }


