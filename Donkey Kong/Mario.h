
#pragma once
#include "gameConfig.h"
#include "Map.h"
#include "Barrel.h"
#include "Point.h"


class Mario
{
	Point position;
	int m_diff_x = (int)gameConfig::Direction::STAY;
	int m_diff_y = (int)gameConfig::Direction::STAY;
	int m_countHeight = (int)gameConfig::Size::ZERO_SIZE;
	int jumpCounter = 0;
	

public:
	Mario() : position((int)gameConfig::Pos::MARIO_X_START, (int)gameConfig::Pos::MARIO_Y_START) {}
	int lives = (int)gameConfig::Size::START_LIVES;
	bool m_isNearExplosion = false;
	enum class State {JUMPING, CLIMBING_UP, CLIMBING_DOWN, WALKING, STANDING};
	State state = State::STANDING;
	Map* map;
	void draw(char) const;
	void move(gameConfig::eKeys key = gameConfig::eKeys::NONE);
	void jump();
	bool isNearWall(int dirX);
	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
	bool isOnFloor();
	bool isUnderFloor();
	bool isNearPaulina();
	char getMapChar();
	bool isUnderLadder();
	bool isOnLadder();
	void climb();
	void downLadder();
	void checkFallHeight();
	void resetMario();
	void checkCollision();
};

