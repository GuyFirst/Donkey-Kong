#pragma once
#include<vector>
#include "Point.h"
#include "Map.h"
#include "gameConfig.h"
#include <iostream>


class Ghost {
public:
    Ghost(Map* map, Point start, int m_id)  : map(map), position(start), startPosition(start), m_id(m_id) { }
    void draw(char ch = 'x') const;
    void move(std::vector<Ghost>& Ghosts);
    Point getPoint() const { return position; }
    void reset();
    bool isOnFloor();

private:
    Point position;
    int m_diff_x = (int)gameConfig::Direction::POSITIVE;
    Map* map;
    Point startPosition;
    int m_id;

    void handleCollision(std::vector<Ghost>& Ghosts);
    void handleDirectionChange();
    bool isNearBoundary() const;
    bool isNearOtherGhosts(const std::vector<Ghost>& Ghosts) const;
};
