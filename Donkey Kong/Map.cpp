#include "Map.h"
#include "general.h"
#include "platform.h"
#include "gameConfig.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "menu.h"
#include <Windows.h>
#include "Point.h"


void Map::printRemainingLives(int remainingLives)
{
    Point startOfText(60, 2);
    gotoxy(startOfText.getX(), startOfText.getY());
    std::cout << "REMAINING LIVES:";
    gotoxy(startOfText.getX() + 4, startOfText.getY() + 1);
    for (int i = 0; i < remainingLives; i++)
        std::cout << "* ";

}
void Map::showMenu() {
    for (int i = 0; i < Map::GAME_HEIGHT; ++i) {
        std::cout << this->loginScreen[i];
        if (i != Map::GAME_HEIGHT - 1)
            std::cout << "\n";
        Sleep(20);
    }
}
void Map::showInstructions()
{
    gotoxy(0, 0);
    for (int i = 0; i < Map::GAME_HEIGHT; ++i) {
        std::cout << this->instructionsScreen[i];
        if (i != Map::GAME_HEIGHT - 1)
            std::cout << "\n";
        Sleep(20);
    }
    char key = 0;
    while (true)
    {
        if (_kbhit())
            key = _getch();

        if (key != (char)gameConfig::eKeys::ESC)
            continue;

        break;
    }
    return;
}
int Map::mainMenu()
{
    int flag = 0;
    showMenu();
    while (true)
    {
        char keyPressed = '*';
        if (_kbhit())
            keyPressed = _getch();

        if (keyPressed == '9')
            return flag = exitGame();

        if (keyPressed == '8')
        {
            clrsrc();
            showInstructions();
            clrsrc();
            showMenu();
            Sleep(500);
        }
        if (keyPressed == '1')
        {
            clrsrc();
            return 1;
        }
        if (keyPressed == '0') // a meme
        {
            int i = 0;
            while (true) {
                std::cout << "WELCOME TO MTA PIZZA" << i << "\n";
                i++;
                Sleep(20);
            }

        } 
    }
}




void Map::win()
{
    const char WinScreen[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH] = {
        "                                                                               ", // 1
        "                                                                               ", // 2
        "                                                                               ", // 3
        "                                                                               ", // 4
        "                                                                               ", // 5
        "                                                                               ", // 6
        "                            ~ ~ ~ YOU ~ ~ ~ WON ~ ~ ~                          ", // 7
        "                                                                               ", // 8
        "                                                                               ", // 9
        "                                                                               ", // 10
        "                                                                               ", // 11
        "                                                                               ", // 12
        "                                                                               ", // 13
        "                                                                               ", // 14
        "                                                                               ", // 15
        "                                       :)                                      ", // 16
        "                                                                               ", // 17
        "                                                                               ", // 18
        "                                                                               ", // 19
        "                                                                               ", // 20
        "                                                                               ", // 21
        "                                                                               ", // 22
        "                                                                               ", // 23
        "                                                                               ", // 24
        "===============================================================================", // 25
    };
    const char message[] = "Returning to the main menu";
    gotoxy(0, 0);

    for (int col = 0; col < 25; col++)
    {
        std::cout << WinScreen[col] << '\n';
    }
    int i = 0;
    Sleep(1000);
    gotoxy(28, 22);
    while (message[i] != '\0')
    {
        std::cout << message[i];
        Sleep((int)gameConfig::Sleep::TEXT_PRINTING_SLEEP);
        i++;
    }
    Sleep(2000);
    return;
}

void Map::lose()
{
    const char LoseScreen[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH] = {
       "                                                                               ", // 1
       "                                                                               ", // 2
       "                                                                               ", // 3
       "                                                                               ", // 4
       "                                                                               ", // 5
       "                                                                               ", // 6
       "                            ~ ~ ~ YOU ~ ~ ~ LOST ~ ~ ~                         ", // 7
       "                                                                               ", // 8
       "                                                                               ", // 9
       "                                                                               ", // 10
       "                                                                               ", // 11
       "                                                                               ", // 12
       "                                      OH NO                                    ", // 13
       "                                      LOSER                                    ", // 14
       "                                                                               ", // 15
       "                                       :(                                      ", // 16
       "                                                                               ", // 17
       "                                                                               ", // 18
       "                                                                               ", // 19
       "                                                                               ", // 20
       "                                                                               ", // 21
       "                                                                               ", // 22
       "                                                                               ", // 23
       "                                                                               ", // 24
       "===============================================================================", // 25
    };
    const char message[] = "Returning to the main menu...";
    gotoxy(0, 0);

    for (int col = 0; col < 25; col++)
    {
        std::cout << LoseScreen[col] << '\n';
    }
    int i = 0;
    Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
    gotoxy(28, 22);
    while (message[i] != '\0')
    {
        std::cout << message[i];
        Sleep(100);
        i++;
    }
    for (int i = 0; i < 3; i++) {
        gotoxy(28 + strlen(message) - 3, 22);
        std::cout << "   ";
        gotoxy(28 + strlen(message) - 3, 22);
        for (int i = 0; i < 3; i++) {
            std::cout << '.';
            Sleep((int)gameConfig::Sleep::WAITING_FOR_MENU_SLEEP);
        }
        Sleep((int)gameConfig::Sleep::WAITING_FOR_MENU_SLEEP);
    }
    return;
}

