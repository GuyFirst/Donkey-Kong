#pragma once
#include "Point.h"
class Entity {
private:
	Point position;
public:
	Entity(int x, int y) : position(x, y) {};
	virtual void move() = 0;

};