
#pragma once
#include "gameConfig.h"
#include "Map.h"
#include "Barrel.h"


class Mario
{
	char m_mario = '@';
	int m_x = (int)gameConfig::Pos::MARIO_X_START; //start point in the middle of the floor
	int m_y = (int)gameConfig::Pos::MARIO_Y_START;//start point one character above the floor
	int m_diff_x = (int)gameConfig::Direction::STAY;
	int m_diff_y = (int)gameConfig::Direction::STAY;
	int m_countHeight = (int)gameConfig::Size::ZERO_SIZE;


public:
	int lives = (int)gameConfig::Size::START_LIVES;
	enum class State {JUMPING, CLIMBING_UP, CLIMBING_DOWN, WALKING, STANDING};
	State state = State::STANDING;
	Map* map;
	void draw(char);
	void move(gameConfig::eKeys key = gameConfig::eKeys::NONE);
	void jump();
	bool isNearWall(int dirX);
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
};

