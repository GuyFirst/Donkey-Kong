#pragma once
#include <iostream>
#include "general.h"
#include "gameConfig.h"

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
       " >>>>>>>>>>>>>>>>>>>>>> ==== ===== ===================================         ", // 8
       "                                                                    H          ", // 9
       "                                                                    H          ", // 10
       "   ========== <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ", // 11
       "         H                         H                                            ", // 12
       "         H                         H                                           ", // 13
       "         H                         H                                            ", // 14
       "         H                         H                                            ", // 15
       "         H                         H                                            ", // 16
       " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>         ", // 17
       "                                                  H                H           ", // 18
       "                                                  H                H           ", // 19
       "                                                  H                H           ", // 20
       "                                                 ==                H           ", // 21
       "                                               ==                  H           ", // 22
       "                              ================                     H           ", // 23
       "                                                                   H           ", // 24
       "===============================================================================", // 25

    };
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
    Map() { resetMap(); printcurrentMap(); }
    void printcurrentMap() { 
        gotoxy(0, 0);
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
            std::cout << currentMap[i] << '\n';
    }

    void printRemainingLives(int remainingLives);
    int mainMenu();
    void showMenu() { 
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
            std::cout << this->loginScreen[i] << '\n';
    }
    void showInstructions();
    int exitGame() {
        std::cout << "Exiting the game. Goodbye!" << std::endl;
        return -1;
    }
    void win();
    void lose();
};

