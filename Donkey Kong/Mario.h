#pragma once

#include "Point.h"
#include "Map.h"
#include "gameConfig.h"

class Mario {
public:
    enum class State {
        STANDING,
        WALKING,
        JUMPING,
        CLIMBING_UP,
        CLIMBING_DOWN
    };

    Mario(Map* map) : position((int)gameConfig::Pos::MARIO_X_START, (int)gameConfig::Pos::MARIO_Y_START), map(map) {}

    void draw(char ch) const;
    void move(gameConfig::eKeys key = gameConfig::eKeys::NONE);
    void jump();
    void climb();
    void downLadder();
    void checkFallHeight();
    void resetMario();

    int getX() const { return position.getX(); }
    int getY() const { return position.getY(); }
	State getState() const { return state; }
    bool isNearPaulina() const;
    char getMapChar() const;
    bool isBarrelHere() const;
   
    void setIsNearExplosion(bool isNear) { m_isNearExplosion = isNear; }
private:
    Point position;
    int m_diff_x = (int)gameConfig::Direction::STAY;
    int m_diff_y = (int)gameConfig::Direction::STAY;
    int m_countHeight = (int)gameConfig::Size::ZERO_SIZE;
    int jumpCounter = 0;
    int lives = (int)gameConfig::Size::START_LIVES;
    bool m_isNearExplosion = false;
    State state = State::STANDING;
    Map* map;

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
    bool checkForCollisions();

  friend class Game;
};

