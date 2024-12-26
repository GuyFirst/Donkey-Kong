#include "gohst.h"
#include <cstdlib> // std::rand
#include <ctime>   // std::time
#include <iostream>
#include <vector>

void gohst::draw(char ch) const {
    gotoxy(position.getX(), position.getY());
    std::cout << ch;
}

void gohst::move(const std::vector<gohst>& ghosts) {
    // Erase ghost from the current position
    draw(map->currentMap[position.getY()][position.getX()]);

    // Handle potential collisions or direction changes
    handleCollision(ghosts);
    handleDirectionChange();

    // Update position
    position.setX(position.getX() + m_diff_x);

    // Draw ghost at the new position
    draw('x');
}

void gohst::handleCollision(const std::vector<gohst>& ghosts) {
    if (isNearBoundary() || isNearOtherGhosts(ghosts)) {
        m_diff_x = -m_diff_x; // Change direction
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
    return position.getX() <= 0 || position.getX() >= gameConfig::GAME_WIDTH - 1;
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
