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


    void move(gameConfig::eKeys key = gameConfig::eKeys::NONE);
    void jump();
    void climb();
    void downLadder();
    void checkFallHeight();
    void resetMario();
	State getState() const { return state; }
    bool isNearPaulina() const;
    char getMapChar() const;
    bool isBarrelHere() const;
	bool isGhostHere() const;
    bool isNearPatish() const;
    void setIsNearExplosion(bool isNear) { m_isNearExplosion = isNear; }



private:
    int m_countHeight = (int)gameConfig::Size::ZERO_SIZE;
    int jumpCounter = 0;
    int lives = (int)gameConfig::Size::START_LIVES;
    bool m_isNearExplosion = false;
    State state = State::WALKING;
    bool isWithPatish;
    bool isFalling = false;

    void handleInput(gameConfig::eKeys key);
    void handleUpKey();
    void handleDownKey();
    void setState(State newState, int diffX, int diffY);
    void executeStateAction();
    void walk();
    void handleFalling();
    bool isCeilingAbove() const;
    void handleCeilingCollision();
    void handleLanding();
    bool isNearWall(int dirX) const;
    bool isOnFloor() const;
    bool isUnderFloor() const;
    bool isUnderFloorWhileMoving() const;
    bool isObstacleAbove(int x) const;
    bool isUnderLadder() const;
    bool isOnLadder() const;
    bool checkForCollisions(int key);
  

	friend class Game; //the game has the ability to change the mario's state
};

