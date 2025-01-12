#include "Entity.h"
#include "gameConfig.h"
#include "Map.h"
#include <iostream>
#include <Windows.h>

bool Entity::isNearBoundry() const {
    if (m_diff_x == (int)gameConfig::Direction::POSITIVE)
        return map->originalMap[getPoint().getY()][getPoint().getX() + 1] == 'Q' || position.getX() >= gameConfig::GAME_WIDTH - 2;
    else
        return map->originalMap[getPoint().getY()][getPoint().getX() - 1] == 'Q' || (position.getX() <= 0);
}

bool Entity::isOnFloor() const {
    return this->map->currentMap[position.getY() + 1][position.getX()] != ' ' &&
        this->map->currentMap[position.getY() + 1][position.getX()] != 'O' &&
        this->map->currentMap[position.getY() + 1][position.getX()] != 'x';
}

void Entity::draw(char ch) const {
    gotoxy(position.getX(), position.getY());
    std::cout << ch;
    map->currentMap[position.getY()][position.getX()] = ch;
}
