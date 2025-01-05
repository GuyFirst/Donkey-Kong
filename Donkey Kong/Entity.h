#pragma once
#include "Point.h"
#include "gameConfig.h"

class Map;
class Entity {
protected:  
    Point position;
    char me;
    int m_diff_x;
    int m_diff_y;
    Map* map;

public:
    Entity(int x, int y, char me, int m_diff_x, int m_diff_y, Map* map)
        : position(x, y), me(me), m_diff_x(m_diff_x), m_diff_y(m_diff_y), map(map) {
    }
    

    Point getPoint() const { return position; }
    int getX() const { return position.getX(); }
    int getY() const { return position.getY(); }

    // Getter for map to be accessed from derived classes
    Map* getMap() const { return map; }
};
