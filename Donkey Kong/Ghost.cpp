#include "Ghost.h"
#include <cstdlib> // std::rand
#include <ctime>   // std::time
#include <iostream>
#include <vector>
#include "general.h"
#include "gameConfig.h"

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
        if (&other == this) {  continue; }

        // Check if two ghosts are on the same row 
        if (this->position.getY() == other.position.getY()) {
            if (other.isNearOtherGhosts()) {
                this->m_diff_x = -this->m_diff_x;
                other.m_diff_x = -other.m_diff_x;
            }
        }
    }
    if (isNearBoundry()) {
        m_diff_x = -m_diff_x; }
}








