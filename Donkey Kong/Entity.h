#pragma once
#include "Point.h"
#include "gameConfig.h"

class Map;
class Entity {

protected:  
    Point startingPosition;
    Point position;
    char me;
    int m_diff_x;
    int m_diff_y;
    Map* map;
    

    virtual bool isNearBoundry() const;
    bool isOnFloor() const;

public:
    Entity(Point startingPosition, char me, int m_diff_x, int m_diff_y, Map* map)
        : startingPosition(startingPosition), position(startingPosition), me(me), m_diff_x(m_diff_x), m_diff_y(m_diff_y), map(map) {
    }

    virtual ~Entity() = default;

    virtual void draw(char ch) const;
    

    Point getPoint() const { return position; }
    int getX() const { return position.getX(); }
    int getY() const { return position.getY(); }
    Map* getMap() const { return map; }
};
