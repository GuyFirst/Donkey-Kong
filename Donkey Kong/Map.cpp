#include "Map.h"
#include "general.h"
#include "platform.h"
#include "gameConfig.h"
#include <iostream>


void Map::draw()
{

	char map[(int)Map::GAME_HEIGHT][(int)Map::GAME_WIDTH] = {"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "Q                                                                         Q",
															 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", };
	gotoxy(Map::MIN_X, Map::MIN_Y);
	for (int i = 0; i < Map::GAME_HEIGHT; i++)
	{
		std::cout << map[i];
		gotoxy(Map::MIN_X, Map::MIN_Y + i + 1);
	}
	

}