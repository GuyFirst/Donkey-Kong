#pragma once
class gameConfig
{
public:
	static constexpr int GAME_WIDTH = 81;
	static constexpr int GAME_HEIGHT = 25;
	static constexpr int SLEEP_DURATION = 95;
	enum class eKeys { LEFT = 'a', UP = 'w', RIGHT = 'd', DOWN = 'x', STAY = 's', ESC = 27 };
	enum class Direction { POSITIVE = 1, NEGATIVE = -1 };
	enum class Size { BARREL_MAX = 10};
};

