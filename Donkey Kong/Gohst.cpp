#include "gohst.h"
#include <cstdlib> // std::rand
#include <ctime>   // std::time
#include <iostream>
#include <vector>

void gohst::draw(char ch) const {
    gotoxy(position.getX(), position.getY());
    std::cout << ch;
    map->currentMap[position.getY()][position.getX()] = ch;
}

void gohst::move(std::vector<gohst>& ghosts) {
    // Erase ghost from the current position
    draw(map->originalMap[position.getY()][position.getX()]);

    // Handle potential collisions or direction changes
    handleCollision(ghosts);
    handleDirectionChange();

    // Update position
    position.setX(position.getX() + m_diff_x);

    // Draw ghost at the new position
    draw('X');
}
void gohst::handleCollision(std::vector<gohst>& ghosts) {
    for (auto& other : ghosts) {
        // Skip checking collision with itself
        if (&other == this) {
            continue;
        }

        // Check if the other ghost is adjacent
        int diffX = abs(other.position.getX() - this->position.getX());
        int diffY = abs(other.position.getY() - this->position.getY());

        if (diffX == 1 && diffY == 0) {
            // Both ghosts should change direction
            this->m_diff_x = -this->m_diff_x;
            other.m_diff_x = -other.m_diff_x;
        }
    }

    // Handle boundary collision
    if (isNearBoundary()) {
        m_diff_x = -m_diff_x;
    }
}

void gohst::handleDirectionChange() {
    // Generate a random number between 1 and 100
    int random = std::rand() % 100 + 1; // מספר בין 1 ל-100

    // If the random number is less than 5, change direction
    if (random <= 5) {
        m_diff_x = -m_diff_x; // Change direction
    }
}


bool gohst::isNearBoundary() const {
    return position.getX() <= 0 || position.getX() >= gameConfig::GAME_WIDTH - 4 ;
}
bool gohst::isNearOtherGhosts(const std::vector<gohst>& ghosts) const {
    for (const auto& other : ghosts) {
        // Skip checking collision with itself
        if (&other == this) {
            continue;
        }

        // Check if the other ghost is adjacent (left, right, up, or down)
        int diffX = abs(other.position.getX() - this->position.getX());
        int diffY = abs(other.position.getY() - this->position.getY());
        if ((diffX == 1 && diffY == 0)) {
            return true; // Ghost is adjacent
        }
    }
    return false; // No collision with any other ghost
}

void gohst::reset() {
    position = startPosition; // Reset to the initial position
}

 