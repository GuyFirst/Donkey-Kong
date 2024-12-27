#pragma once
#include<vector>
#include "Point.h"
#include "Map.h"
#include "gameConfig.h"

class gohst {
public:
    gohst(Map* map, Point start)
        : map(map), position(start), startPosition(start) {
    }
    void draw(char ch = 'x') const;
    void move(std::vector<gohst>& ghosts);
    Point getPoint() const { return position; }
    void reset();

private:
    Point position;
    int m_diff_x = (int)gameConfig::Direction::POSITIVE; 
    Map* map;
    Point startPosition;

    void handleCollision(std::vector<gohst>& ghosts);
    void handleDirectionChange();
    bool isNearBoundary() const;
    bool isNearOtherGhosts(const std::vector<gohst>& ghosts) const;
};
