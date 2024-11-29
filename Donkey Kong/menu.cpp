#include<iostream>
#include <cstdlib>
#include <conio.h>
#include "menu.h"
#include <Windows.h>
#include "general.h"
#include "Map.h"



void menu::mainMenu()
{
    showMenu();
    while (true)
    {
        char keyPressed = '=';
        if (_kbhit())
            {
                keyPressed = _getch();
            } 


        if(keyPressed == '9')
                 exitGame();
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
                 return;
        }
        if (keyPressed == '0')
        {
                int i=0;
                while (true) {
                    std::cout << "WELCOME TO MTA PIZZA" << i << "\n";
                    i++;
                    Sleep(20);
                }

        }
    }
}

void menu::showMenu() {
 
    for (int i = 0; i < Map::GAME_HEIGHT; ++i)
        std::cout << this->loginScreen[i] << '\n';
    return;

}

void menu::showInstructions() {
    gotoxy(0, 0);
    for (int i = 0; i < Map::GAME_HEIGHT; ++i)
        std::cout << this->instructionsScreen[i] << '\n';
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

void menu::exitGame() {
    std::cout << "Exiting the game. Goodbye!" << std::endl;
    std::exit(0);
}