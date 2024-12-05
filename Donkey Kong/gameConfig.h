#pragma once
#include "Map.h"
class gameConfig
{
public:
	static constexpr int GAME_WIDTH = 81;
	static constexpr int GAME_HEIGHT = 25;
	static constexpr int SLEEP_DURATION = 100;
	enum class eKeys { LEFT = 'a', UP = 'w', RIGHT = 'd', DOWN = 'x', STAY = 's', ESC = 27, NONE };
	enum class Direction { POSITIVE = 1, NEGATIVE = -1 , STAY = 0};
	enum class Size { BARREL_MAX = 10, ZERO_SIZE = 0, START_LIVES = 3};
	enum class Pos { BARREL_X_START = 5, BARREL_Y_START = 4, MARIO_X_START = (int)Map::GAME_WIDTH / 2, MARIO_Y_START = (int)Map::GAME_HEIGHT - 2};
};

