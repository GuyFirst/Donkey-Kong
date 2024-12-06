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
        flag = startGame();
        if (flag == 1)
            menu.win();
        else
            menu.lose();

    }
    return;
}

int Game::startGame()
{
    ShowConsoleCursor(false);
    int currLives = (int)gameConfig::Size::START_LIVES;

    Barrel arrB[(int)gameConfig::Size::BARREL_MAX] = {};
    int barrelCurr = 0;
    int barrelCounter = 0;

    Map m;
    m.resetMap();
    m.printMap();
    m.printRemainingLives(currLives);
    Mario mario;
    mario.map = &m;
    char keyPressed = (char)(gameConfig::eKeys::STAY);
    bool isLocked = false;
    

    while (true) {
        keyPressed = 0;
        
        if (_kbhit() ) {
            keyPressed = _getch();

            // Pause the game if ESC is pressed
            if (keyPressed == (int)gameConfig::eKeys::ESC) {
                pause();
                m.printMap();
            }
        }
        barrelCounter++;
        
        // Handle losing a life
        if (currLives != mario.lives) {
            if (currLives == 1)
               return -1; // End the game if no lives remain
            loseALife();  
            m.resetMap(); 
            m.printMap(); 
            currLives--; // Decrease the remaining lives
            m.printRemainingLives(currLives);
            mario.resetMario(); // Reset Mario's position and state
            barrelCurr = 0;     // Reset the barrels
            barrelCounter = 0;
            isLocked = false;   // Unlock Mario after resetting
        }

        // Check if Mario has reached Paulina
        if (mario.isNearPaulina()) {
            return 1; // Player wins the game
        }

        // Draw Mario on the map
        char curr = mario.getMapChar();
        if (curr == 'H')
            mario.draw('#');
        else
            mario.draw('@');

        // Spawn new barrels periodically
        if (barrelCounter == 20 && barrelCurr < (int)gameConfig::Size::BARREL_MAX) {
            arrB[barrelCurr].addBarrel(arrB, barrelCurr);
            arrB[barrelCurr].map = &m;
            barrelCurr++;
            barrelCounter = 0;
        }

        // Move all barrels
        for (int i = 0; i < barrelCurr; i++) {
            curr = arrB[i].getMapChar();
            arrB[i].draw('O');
            arrB[i].move();
        }

        Sleep(gameConfig::SLEEP_DURATION);

        if (isLocked) {
            // If locked, check for the 's' key to allow stopping on the ladder
            if (keyPressed == (char)gameConfig::eKeys::STAY &&
                (mario.state == Mario::State::CLIMBING_UP || mario.state == Mario::State::CLIMBING_DOWN)) {
                mario.state = Mario::State::STANDING; // Stop Mario on the ladder
                isLocked = false; // Unlock to allow further movement
                continue; // Skip the rest of the loop to process the state change
            }
            else {
                // Continue the current action
                mario.move(); // Use the current state without new input
            }
        }
        else {
            // If not locked, process the user's input
            mario.move((gameConfig::eKeys)keyPressed);

            // Lock Mario if a long action starts
            if (mario.state == Mario::State::JUMPING ||
                mario.state == Mario::State::CLIMBING_UP ||
                mario.state == Mario::State::CLIMBING_DOWN) {
                isLocked = true;
            }
        }

        // Unlock Mario when the action finishes
        if (mario.state == Mario::State::STANDING || mario.state == Mario::State::WALKING) {
            isLocked = false;
        }

        keyPressed = 0; // Reset the input
    }

    return 0;
}


void Game::pause()
{
    clrsrc();
    gotoxy(20, 10);
    std::cout << "Game paused, press ESC again to continue.";
    gotoxy(20, 12);
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
    Sleep(500);
    clrsrc();
    gotoxy(40, 10);
    std::cout << "oh no u lose a life oh no";
    Sleep(1000);
}




