#pragma once

#include "Point.h"
#include "Map.h"
#include "gameConfig.h"
#include "Entity.h"

class Mario : public Entity {
public:
    enum class State {
        STANDING,
        WALKING,
        JUMPING,
        CLIMBING_UP,
        CLIMBING_DOWN,
        FALLING
    };

    Mario(Map* map, Point startingPoint)
        : Entity(startingPoint, '@',
           (int)gameConfig::Direction::STAY, (int)gameConfig::Direction::STAY, map),
        isWithPatish(false) {
    }  
	State getState() const     { return state; }
    bool isNearPaulina() const { return this->map->currentMap[position.getY()][position.getX() + m_diff_x] == '$'; }
    char getMapChar() const    { return this->map->originalMap[position.getY()][position.getX()]; }
    bool isBarrelHere() const  { return this->map->currentMap[position.getY()][position.getX()] == 'O'; }
    bool isGhostHere() const   { return this->map->currentMap[position.getY()][position.getX()] == 'x'; }
    bool isNearPatish() const  { return this->map->originalMap[position.getY()][position.getX()] == 'p'; }
    void setIsNearExplosion(bool isNear) { m_isNearExplosion = isNear; }



private:
    int m_countHeight = (int)gameConfig::Size::ZERO_SIZE;
    int jumpCounter = 0;
    int lives = (int)gameConfig::Size::START_LIVES;
    bool m_isNearExplosion = false;
    State state = State::WALKING;
    bool isWithPatish;
    bool isFalling = false;
    void draw(char ch) const;
    void move(gameConfig::eKeys key = gameConfig::eKeys::NONE);
    void jump();
    void climb();
    void downLadder();
    void resetMario();
    void handleInput(gameConfig::eKeys key);
    void handleUpKey();
    void handleDownKey();
    void setState(State newState, int diffX, int diffY);
    void executeStateAction();
    void walk();
    void handleFalling();
    void handleCeilingCollision();
    void handleLanding();
    bool isNearWall(int dirX) const;
    bool isOnFloor() const;
    bool isUnderFloor() const;
    bool isUnderFloorWhileMoving() const;
    bool isUnderLadder() const;
    bool isOnLadder() const;
    bool checkForCollisions(int key);
    bool isObstacleAbove(int x) const { return this->map->currentMap[position.getY() - 1][x] != ' ' && this->map->currentMap[position.getY() - 1][x] != 'H'; }
    bool isCeilingAbove() const       { return this->map->currentMap[position.getY() - 1][position.getX()] != ' ' &&
                                               this->map->currentMap[position.getY() - 1][position.getX()] != 'H';
    }
    void checkFallHeight() { if (m_countHeight >= 5) { lives--; } }

	friend class Game; //the game has the ability to change the mario's state
};

