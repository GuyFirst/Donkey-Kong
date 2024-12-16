#pragma once
class gameConfig
{
public:
	static constexpr int GAME_WIDTH = 81;
	static constexpr int GAME_HEIGHT = 25;
	enum class eKeys { LEFT = 'a', UP = 'w', RIGHT = 'd', DOWN = 'x', STAY = 's', ESC = 27, NONE };
	enum class Direction { POSITIVE = 1, NEGATIVE = -1 , STAY = 0};
	enum class Size { BARREL_MAX = 6, ZERO_SIZE = 0, START_LIVES = 3, BARRREL_COUNTER = 25};
	enum class Sleep {GAME_LOOP_SLEEP = 110, SCREEN_SLEEP = 900, EXPLOSION_SLEEP = 35, TEXT_PRINTING_SLEEP = 95, WAITING_FOR_MENU_SLEEP = 150};
	enum class Pos { BARREL_X_START = 31, BARREL_Y_START = 4, MARIO_X_START = (int)gameConfig::GAME_WIDTH / 2, MARIO_Y_START = (int)gameConfig::GAME_HEIGHT - 2};

	//general functions
	void gotoxy(int, int);
	void clrsrc();
	void ShowConsoleCursor(bool showFlag);
};

