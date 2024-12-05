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
       "    |OOO|                                                                      ", // 3
       "   |OOOOO|&  $                                                                 ", // 4
       "   ==  ==========                                                              ", // 5
       "                H                                                              ", // 6
       "                H                                                              ", // 7
       " >>>>>>>>>>>>>>>>>>> >> >>>> >>>>> >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>         ", // 8
       "                                                                    H          ", // 9
       "                                                                    H          ", // 10
       "   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ", // 11
       "         H                                                                     ", // 12
       "         H                                                                     ", // 13
       "         H                                                                     ", // 14
       "         H                                                                     ", // 15
       "         H                                                                     ", // 16
       " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>         ", // 17
       "                                                  H                H           ", // 18
       "                                                  H                H           ", // 19
       "                                                  H                H           ", // 20
       "                                                 ==                H           ", // 21
       "                                               ==                  H           ", // 22
       "                                            ==                     H           ", // 23
       "                                                                   H           ", // 24
       "===============================================================================", // 25

    };
    char currentMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {};
    void resetMap() {
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
            memcpy(currentMap[i], originalMap[i], Map::GAME_WIDTH);
    }
    void printMap();
    void printOGMap();
    void printRemainingLives(int remainingLives);
};

