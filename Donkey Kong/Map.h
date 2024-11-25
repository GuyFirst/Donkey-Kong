#pragma once
#include "point.h"
#include <iostream>
#include "general.h"
class Map
{
public:
    static constexpr int GAME_WIDTH = 76;
    static constexpr int GAME_HEIGHT = 23;
     const char originalMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                         =======================                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                            =====================                        Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "Q                                                                         Q",
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"
    };
	static constexpr int MIN_X = 2;
	static constexpr int MIN_Y = 2;
	char currentMap[Map::GAME_HEIGHT][Map::GAME_WIDTH + 1] = {};
	void resetBoard() {
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
            memcpy(currentMap[i], originalMap[i], Map::GAME_WIDTH + 1);
	}
    void printMap() {
        gotoxy(Map::MIN_X, Map::MIN_Y);
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
        {
            std::cout << currentMap[i];
            gotoxy(Map::MIN_X, Map::MIN_Y + i + 1);
        }
    }
};

