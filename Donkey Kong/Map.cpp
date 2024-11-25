#include "Map.h"
#include "general.h"
#include "platform.h"
#include "gameConfig.h"
#include <iostream>

void Map::printMap()
{
        gotoxy(Map::MIN_X, Map::MIN_Y);
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
        {
            std::cout << currentMap[i];
            gotoxy(Map::MIN_X, Map::MIN_Y + i + 1);
        }
}
