#pragma once
#include <iostream>
#include "general.h"
class Map
{
public:
    static constexpr int GAME_WIDTH = 81;
    static constexpr int GAME_HEIGHT = 25;
     const char originalMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {
        "                                                                               ", // 1
        "                                                                               ", // 2
        "                                   $                                           ", // 3
        "          &            ==================================                      ", // 4
        "         ========                                                              ", // 5
        "                                                                               ", // 6
        "                                                                               ", // 7
        "                                                                               ", // 8
        "                                                                               ", // 9
        "     =======================                                                   ", // 10
        "                                                                               ", // 11
        "=====                                              ======================      ", // 12
        "                                                                               ", // 13
        "                                                                               ", // 14
        "                                 =============================                 ", // 15
        "==========                                                                     ", // 16
        "                                                                               ", // 17
        "                                                                               ", // 18
        "             =========H========                                                ", // 19
        "                      H                                                        ", // 20
        "                      H             ========H====================              ", // 21
        "                      H                     H                                  ", // 22
        "                      H                     H                                  ", // 23
        "                      H                     H                                  ", // 24
        "===============================================================================", // 25
      
    };
	char currentMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {};
	void resetMap() {
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
            memcpy(currentMap[i], originalMap[i], Map::GAME_WIDTH + 1);
	}
    void printMap();
};

