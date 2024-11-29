#include "Game.h"
#include "gameConfig.h"
#include <conio.h> //for kbhit_ getch
#include <Windows.h>

#include "Map.h"
#include "Mario.h"
#include "general.h"
#include "menu.h"
void Game::run()
{
   menu menu;
   menu.mainMenu();
   startGame(); 
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
        if (curr == 'H')
            mario.draw('#');
        else
            mario.draw('@');
        Sleep(gameConfig::SLEEP_DURATION);
       
        mario.draw(curr);

        mario.move((gameConfig::eKeys)keyPressed);
        keyPressed = 0;
    }
    return;
}
