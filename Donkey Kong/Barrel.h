#pragma once
#include "gameConfig.h"
#include "Map.h"
#include "Point.h"
#include <vector>
#include "Entity.h"
class Mario;

class Barrel : public Entity {
    int m_prev_diff_x = 0;
    int m_fallCounter = 0;

 

    // Helper methods
    void updatePosition();
    void handleExplosion(Mario* mario);
    bool isOnAir(char& refFloor);
    bool isNearWall(int dirX) const;
    bool checkFallHeight();
    bool isMarioNearMe(Point marioPos) const;

public:
    
    static int barrelCurr;
    static int barrelSpawnCounter;

    Barrel(Map* map) : Entity((int)gameConfig::Pos::BARREL_X_START, (int)gameConfig::Pos::BARREL_Y_START, 'O',
        (int)gameConfig::Direction::STAY, (int)gameConfig::Direction::POSITIVE, map) {
    }

    Barrel() : Entity((int)gameConfig::Pos::MARIO_X_START, (int)gameConfig::Pos::MARIO_Y_START, 'O',
        (int)gameConfig::Direction::STAY, (int)gameConfig::Direction::POSITIVE, nullptr) {
    }

    void move(Mario* mario);
    void draw(char ch) const;
    void reset();
    void addBarrel(std::vector<Barrel>& barrels, Map* map);  

   
    static int getBarrelCurr() {  return barrelCurr;  }

    static int getBarrelSpawnCounter() { return barrelSpawnCounter; }

    static void incrementBarrelCurr() {barrelCurr++; }

    static void resetBarrelSpawnCounter() { barrelSpawnCounter = 0; }

   
    char getMapChar() const { return this->getMap()->originalMap[position.getY()][position.getX()]; }
};
