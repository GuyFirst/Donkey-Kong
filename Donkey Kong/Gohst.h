#pragma once

#include "Point.h"
#include "Map.h"
#include "gameConfig.h"

class gohst {
public:
    gohst(Map* map, Point position)
        :  map(map), position(position) {
    }

    void draw(char ch = 'x') const;
    void move(const std::vector<gohst>& ghosts);
    Point getPoint() const { return position; }

private:
    Point position;
    int m_diff_x = (int)gameConfig::Direction::POSITIVE; 
    Map* map;

    void handleCollision(const std::vector<gohst>& ghosts);
    void handleDirectionChange();
    bool isNearBoundary() const;
    bool isNearOtherGhosts(const std::vector<gohst>& ghosts) const;
};
