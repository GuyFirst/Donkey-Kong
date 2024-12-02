#include "Game.h"
#include "gameConfig.h"
#include <conio.h> //for kbhit_ getch
#include <Windows.h>
#include "Barrel.h"
#include "Map.h"
#include "Mario.h"
#include "general.h"
#include "menu.h"

void Game::run()
{
    int flag = 0;
    while (true)
    {
        gotoxy(0, 0);
        menu menu;
        flag = menu.mainMenu();
        if (flag == -1)
            return;
        startGame();
        menu.win();

    }
    return;
}

void Game::startGame()
{
    ShowConsoleCursor(false);
    Map m;
    m.resetMap();
    m.printMap();
    Mario mario;
    mario.map = &m;
    Barrel b;
    b.map = &m;
    char keyPressed = (char)(gameConfig::eKeys::STAY);
    while (true) {
        keyPressed = 0;
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (int)gameConfig::eKeys::ESC) {
                std::cout << "Exiting to main menu..." << std::endl;
                break;
            }
        }


        char curr = mario.getMapChar();
        if (mario.isNearPaulina()) {

            break;
        }
        if (curr == 'H')
            mario.draw('#');
        else
            mario.draw('@');

        curr = b.getMapChar();

        b.draw('O');

        Sleep(gameConfig::SLEEP_DURATION);
        curr = mario.getMapChar();
        mario.draw(curr);
        curr = b.getMapChar();
        b.draw(curr);
        b.move();
        mario.move((gameConfig::eKeys)keyPressed);




        keyPressed = 0;
    }
    return;
}


