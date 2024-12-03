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
       "     |O|                                                                       ", // 2
       "    |OOO|                          $                                           ", // 3
       "   |OOOOO|&            ==================================================      ", // 4
       "   ==  ==========          H                                                   ", // 5
       "                           H                                                   ", // 6
       "  >>>>>>>>>>>>>>>>>>>>>=======                                                 ", // 7
       "       H                      ====                                             ", // 8
       "       H                          ======  ======  ==== =====                   ", // 9
       "       H                                   H             H                     ", // 10
       "       H                                   H             H                     ", // 11
       "===========                                H       ======================      ", // 12
       "         H                                 H                    H              ", // 13
       "         H                                 H                    H              ", // 14
       "         H              <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<         H              ", // 15
       "        <<<<<<<<<<<<                                            H              ", // 16
       "              H                                                 H              ", // 17
       "              H                                                 H              ", // 18
       "             ==================                                 H              ", // 19
       "                      H                                         H              ", // 20
       "                      H             =============================              ", // 21
       "                      H                     H                                  ", // 22
       "                      H                     H                                  ", // 23
       "                      H                     H                                  ", // 24
       "===============================================================================", // 25

    };
    char currentMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {};
    void resetMap() {
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
            memcpy(currentMap[i], originalMap[i], Map::GAME_WIDTH);
    }
    void printMap();
};

