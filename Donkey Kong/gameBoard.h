#pragma once
#include "point.h"
class gameBoard
{
	point board[4];
	enum class CORNER {TOP_LEFT = 0, TOP_RIGHT = 1, BOTTOM_RIGHT = 2, BOTTOM_LEFT = 3 };
public:
	void draw(point board[4]);
};

