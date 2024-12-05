#include "Map.h"
#include "general.h"
#include "platform.h"
#include "gameConfig.h"
#include <iostream>

void Map::printMap()
{
    gotoxy(0, 0);
    for (int i = 0; i < Map::GAME_HEIGHT; ++i)
    {
        std::cout << currentMap[i] << '\n';
    }
}
void Map::printOGMap()
{
    for (int i = 0; i < Map::GAME_HEIGHT; ++i)
    {
        std::cout << originalMap[i] << '\n';
    }
}

void Map::printRemainingLives(int remainingLives)
{
    gotoxy(60, 2);
    std::cout << "REMAINING LIVES:";
    gotoxy(64, 3);
    for (int i = 0; i < remainingLives; i++)
        std::cout << "* ";

}
