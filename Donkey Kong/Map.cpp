#include "Map.h"
#include "general.h"
#include "platform.h"
#include "gameConfig.h"
#include <iostream>

void Map::printMap()
{
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
        {
            std::cout << currentMap[i] << '\n';
        }
}
