//#pragma once
//#include "gameConfig.h"
//#include "Map.h"
//#include "Point.h"
//
//class Mario;
//class Barrel
//{
//	Point position;
//	enum class numbers { MAX_BARRELS = 7 };
//	int m_x = (int)gameConfig::Pos::BARREL_X_START; //first apperance of any barrel
//	int m_y = (int)gameConfig::Pos::BARREL_Y_START;
//	int m_diff_x = (int)gameConfig::Direction::STAY;
//	int m_diff_y = (int)gameConfig::Direction::POSITIVE;
//	int m_prev_diff_x = 0;
//	int m_fallCounter = 0;
//
//public:
//	Barrel() : position((int)gameConfig::Pos::BARREL_X_START, (int)gameConfig::Pos::BARREL_Y_START) {}
//	Map* map;
//	bool checkFallHeight(); // return 1 if exploded 0 if not
//	void move(Mario* mario);
//	void draw(char ch);
//	bool isOnFloor(char& refFloor);
//	void addBarrel(Barrel barrelArr[], int size);
//	bool isOnAir(char& refFloor);
//	bool isNearWall(int dirX);
//	char getMapChar() { return this->map->originalMap[m_y][m_x]; }
//	void reset();
//	bool isMarioNearMe(Point pos);
//};
#pragma once
#include "gameConfig.h"
#include "Map.h"
#include "Point.h"

class Mario;

class Barrel {
    Point position;
    int m_diff_x = (int)gameConfig::Direction::STAY;
    int m_diff_y = (int)gameConfig::Direction::POSITIVE;
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
    Barrel() : position((int)gameConfig::Pos::BARREL_X_START, (int)gameConfig::Pos::BARREL_Y_START) {}
    Map* map;

    // Public methods
    void move(Mario* mario);
    void draw(char ch) const;
    void reset();
    void addBarrel(Barrel barrelArr[], int size);
    char getMapChar() const { return this->map->originalMap[position.getY()][position.getX()]; }
};

