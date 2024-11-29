#include<iostream>
#include <cstdlib>
#include <conio.h>
#include "menu.h"
#include <Windows.h>
#include "general.h"



void menu::mainMenu()
{
    showMenu();
    while (true)
    {
        char keyPressed = '\0';
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
       
    }
}

void menu::showMenu() {
 

    std::cout << "=====================" << std::endl;
    std::cout << "  Welcome to Donkey Kong  " << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "8. Game Instructions" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "Please select an option: ";
    return;

}

void menu::startGame() {
    std::cout << "Starting a new game..." << std::endl;
    return;
}

void menu::showInstructions() {
    char key = 0;
    std::cout << "=====================" << std::endl;
    std::cout << "  Game Instructions  " << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "1. Use A (left), W (up), D (right), X (down), S (stand) keys to move Mario." << std::endl;
    std::cout << "2. Avoid barrels." << std::endl;
    std::cout << "3. Reach to the princess to win!" << std::endl;
    std::cout << "4. Have fun!" << std::endl;
    std::cout << "Press esc key to return to the main menu..." << std::endl;
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