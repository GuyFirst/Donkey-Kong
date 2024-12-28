#pragma once
#include "gameConfig.h"
#include "Map.h"
#include "Point.h"
#include <vector>  
class Mario;

class Barrel {
    Point position;
    int m_diff_x = (int)gameConfig::Direction::STAY;
    int m_diff_y = (int)gameConfig::Direction::POSITIVE;
    int m_prev_diff_x = 0;
    int m_fallCounter = 0;
    Map* map;

    // Helper methods
    void updatePosition();
    void handleExplosion(Mario* mario);
    bool isOnAir(char& refFloor);
    bool isNearWall(int dirX) const;
    bool checkFallHeight();
    bool isMarioNearMe(Point marioPos) const;

public:
    Barrel(Map* map) : position((int)gameConfig::Pos::BARREL_X_START, (int)gameConfig::Pos::BARREL_Y_START), map(map) {}
    Barrel() : position((int)gameConfig::Pos::BARREL_X_START, (int)gameConfig::Pos::BARREL_Y_START) {}

    void move(Mario* mario);
    void draw(char ch) const;
    void reset();
    void addBarrel(std::vector<Barrel>& barrels, Map* map);  // Change to vector reference
    char getMapChar() const { return this->map->originalMap[position.getY()][position.getX()]; }
};
