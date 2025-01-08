#pragma once
#include <iostream>
#include "general.h"
#include "gameConfig.h"
#include <Windows.h>
#include "Point.h"
#include <string>
#include <vector>

class Map
{

private: 
    Point marioStartPos;
    Point barrelStartPoint;
    Point legendPosition;
    Point patishPosition;
    std::vector<Point> ghostStartPositions;


public:
    static constexpr int GAME_WIDTH = 82;
    static constexpr int GAME_HEIGHT = 25;
    Point legendTopLeft;
	Point getPatishPosition() const { return patishPosition; }
    Point getMarioStartPos() const { return marioStartPos; }
    Point getBarrelStartPoint() const { return barrelStartPoint; }
    Point getLegendPosition() const { return legendPosition; }
    const std::vector<Point>& getGhostStartPositions() const { return ghostStartPositions; }


    char originalMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {};

    const char loginScreen[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {

       "                                 ================                              ", 
       "                                    Welcome to                                 ", 
       "                                 ================                              ", 
       "       ________  ________  ________   ___  __    _______       ___    ___      ", 
       "      |\\   ___ \\|\\   __  \\|\\   ___  \\|\\  \\|\\  \\ |\\  ___ \\     |\\  \\  /  /|      ", 
       "      \\ \\  \\_|\\ \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\/  /|\\ \\   __/|    \\ \\  \\/  / /", 
       "       \\ \\  \\ \\\\ \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\   ___  \\ \\  \\_|/__   \\ \\    / / ", 
       "        \\ \\  \\_\\\\ \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\   \\/  /  /", 
       "         \\ \\_______\\ \\_______\\ \\__\\\\ \\__\\ \\__\\\\ \\__\\ \\_______\\__/  / / ", 
       "          \\|_______|\\|_______|\\|__| \\|__|\\|__| \\|__|\\|_______|\\___/ /       ", 
       "                                                              \|___|/  ", 
       "                           by Guy First and Ori Perelman                       ",  
       "                      |\\  \\|\\  \\ |\\   __  \\|\\   ___  \\|\\   ____\\", 
       "                      \\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\___| ", 
       "                       \\ \\   ___  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\  ___ ", 
       "                        \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ ", 
       "                         \\ \\__\\\\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\  ", 
       "                          \\|__| \\|__|\\|_______|\\|__| \\|__|\\|_______|",
       "                                                                               ",
       "                             Please press the following keys to:               ", 
       "                               1. Start Game                                   ", 
       "                               8. Show Instructions                            ",
       "                               9. Exit                                         ", 
       "                                                                               ", 

    };

    const char instructionsScreen[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {
        "                                                                               ", // 1
        "                                                                               ", // 2
        "                                                                               ", // 3
        "                                                                               ", // 4
        "                                                                               ", // 5
        "                              ======================                           ", // 6
        "                                 Game Instructions                             ", // 7
        "                              ======================                           ", // 8
        "                                                                               ", // 9
        "                     1. Use A (left), W (up), D (right), X (down),             ", // 10
        "                            S (stand) keys to move Mario.                      ", // 11
        "                                                                               ", // 12
        "                                2. Avoid barrels.                              ", // 13
        "                                                                               ", // 14
        "                         3. Reach to the princess to win!                      ", // 15
        "                                                                               ", // 16
        "                                   4. Have fun!                                ", // 17
        "                                                                               ", // 18
        "                     Press the ESC key to return to the main menu...           ", // 19
        "                                                                               ", // 20
        "                                                                               ", // 21
        "                                                                               ", // 22
        "                                                                               ", // 23
        "                                                                               ", // 24
        "===============================================================================", // 25

    };
    char currentMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {};
   
    void resetMap() {
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
            memcpy(currentMap[i], originalMap[i], Map::GAME_WIDTH);
    }

    
    void printcurrentMap() { 
        gotoxy(0, 0);
        for (int i = 0; i < Map::GAME_HEIGHT; ++i) {
            std::cout << currentMap[i];
            if (i != Map::GAME_HEIGHT - 1)
            Sleep(20);
        }
    }
    

    char chooseScreens(std::vector<std::string> vec_to_fill);
    void printLegend(int remainingLives);
    int mainMenu(std::vector<std::string> vec_to_fill);
    void showMenu();
    void showInstructions();
    int exitGame() { std::cout << "Exiting the game. Goodbye!" << std::endl; return -1; }
    void win();
    void lose();
    void printClock(int& secondsElapsed);
    void load(const std::string& filename);

   
};

