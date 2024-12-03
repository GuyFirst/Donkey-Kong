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
    Barrel arrB[(int)gameConfig::Size::BARREL_MAX] = {};
    int barrelCurr = 0;
    int counter = 0;
    int currLives = 3;
    char keyPressed = (char)(gameConfig::eKeys::STAY);
    while (true) {
        keyPressed = 0;
        if (_kbhit()) {
            keyPressed = _getch();
         
            if (keyPressed == (int)gameConfig::eKeys::ESC) {
                pause();
                m.printMap();
            }
        }
        counter++;
        if (currLives != mario.lives)
        {
            loseALife();
            Sleep(1000);
            clrsrc();
            m.resetMap();
            gotoxy(0, 0);
            m.printMap();
            currLives--;
            // reser mario to his first location and destroy all barrels
        }
        char curr = mario.getMapChar();
        if (mario.isNearPaulina()) {

            break;
        }
        if (curr == 'H')
            mario.draw('#');
        else
            mario.draw('@');

        if (counter == 12 && barrelCurr < (int)gameConfig::Size::BARREL_MAX)
        {
            arrB[barrelCurr].addBarrel(arrB, barrelCurr);
            arrB[barrelCurr].map = &m;
            barrelCurr++;
            counter = 0;
        }
        for (int i = 0; i < barrelCurr; i++)
        {
            curr = arrB[i].getMapChar();
            arrB[i].draw('O');
        }
        Sleep(gameConfig::SLEEP_DURATION);
        curr = mario.getMapChar();
        mario.draw(curr);
        if (barrelCurr)
        {
            for (int i = 0; i < barrelCurr; i++)    //barrel movemant
            {
                curr = arrB[i].getMapChar();
                arrB[i].draw(curr);
                arrB[i].move();
            }
        }
        mario.move((gameConfig::eKeys)keyPressed, arrB, barrelCurr);




        keyPressed = 0;
    }
    return;
}

void Game::pause()
{
    clrsrc();
    gotoxy(40, 10);
    std::cout << "Game paused, press ESC again to continue.";
    gotoxy(40, 12);
    std::cout<<"But it is not mandatory to present such a message.";
    char keyPressed = 0;
   
    while (true) {
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (char)gameConfig::eKeys::ESC) {
                clrsrc();
                gotoxy(0, 0);
                return;
            }

        }
    }
}

void Game::loseALife()
{
    clrsrc();
    gotoxy(40, 10);
    std::cout << "oh no u lose a life oh no";

}




