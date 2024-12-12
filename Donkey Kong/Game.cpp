#include "Game.h"
#include "gameConfig.h"
#include <conio.h> //for kbhit_ getch
#include <Windows.h>
#include "Barrel.h"
#include "Map.h"
#include "Mario.h"
#include "Point.h"

void Game::run()
{
    int flag = 0;                                  
    Point screenStart(0, 0);
    while (true)                                        //
    {                                                   //
        gotoxy(screenStart.getX(), screenStart.getY()); // 
        Map menu;                                       // the flags indicates if the player wins, loses, or quiting the game.
        flag = menu.mainMenu();                         //  -1 for deciding to quit (before we entered the game)
        if (flag == -1)                                 //   1 if the player won
            return;                                     //  -1 if the player lost
        flag = startGame();                             //
        if (flag == 1)                                  //
            win();                                      //
        else                                            //
            lose();
    }
    return;
}

int Game::startGame()
{
    ShowConsoleCursor(false);

    Barrel arrBarrels[(int)gameConfig::Size::BARREL_MAX] = {};           
    int barrelCurr = (int)gameConfig::Size::ZERO_SIZE;
    int barrelCounter = (int)gameConfig::Size::ZERO_SIZE;
    Point explosionPos;
    Map gameBoard;

    
    Mario mario(&gameBoard);

    int currLives = (int)gameConfig::Size::START_LIVES;
    gameBoard.printRemainingLives(currLives);

    char keyPressed = (char)(gameConfig::eKeys::STAY);
    bool isMarioLocked = false;
    
    //start of the game loop
    while (true) {
        keyPressed = (int)gameConfig::eKeys::NONE;
        
        if (_kbhit() ) {
            keyPressed = std::tolower(_getch());

            // Pause the game if ESC is pressed
            if (keyPressed == (int)gameConfig::eKeys::ESC) {
                pause();
                gameBoard.printcurrentMap();
            }
        }
        barrelCounter++;
        
        // Handle losing a life
        if (currLives != mario.lives) {
            if (currLives == 1)
               return -1; // End the game if no lives remain
            loseALife();  
            gameBoard.resetMap(); 
            gameBoard.printcurrentMap(); 
            currLives--; 
            gameBoard.printRemainingLives(currLives);
            mario.resetMario(); 
            barrelCurr = 0;     
            barrelCounter = 0;
            isMarioLocked = false;   
        }

        // Check if Mario has reached Paulina
        if (mario.isNearPaulina()) {
            return 1;                   // Player wins the game
        }

        // Draw Mario on the map
        char curr = mario.getMapChar();
        if (curr == 'H')
            mario.draw('#');
        else
            mario.draw('@');

        // Spawn new barrels periodically
        if (barrelCounter == 25 && barrelCurr < (int)gameConfig::Size::BARREL_MAX) {
            arrBarrels[barrelCurr].addBarrel(arrBarrels, barrelCurr, &gameBoard);
            //arrBarrels[barrelCurr].map = &gameBoard;
            barrelCurr++;
            barrelCounter = 0;
        }

        // Move all barrels
        for (int i = 0; i < barrelCurr; i++) {
            curr = arrBarrels[i].getMapChar();
            arrBarrels[i].draw('O');
            arrBarrels[i].move(&mario);
        }

        Sleep((int)gameConfig::Sleep::GAME_LOOP_SLEEP);

        if (isMarioLocked) {
            // If locked, check for the 's' key to allow stopping on the ladder
            if (keyPressed == (char)gameConfig::eKeys::STAY && (mario.state == Mario::State::CLIMBING_UP || mario.state == Mario::State::CLIMBING_DOWN))
            {
                mario.state = Mario::State::STANDING; 
                isMarioLocked = false; 
                continue; 
            }
            else
                mario.move(); 
        }
        else 
        {
            mario.move((gameConfig::eKeys)keyPressed);
            // Lock Mario if a long action starts
            if (mario.state == Mario::State::JUMPING || mario.state == Mario::State::CLIMBING_UP || mario.state == Mario::State::CLIMBING_DOWN)
                isMarioLocked = true;
        }

        // Unlock Mario when the action finishes
        if (mario.state == Mario::State::STANDING || mario.state == Mario::State::WALKING) {
            isMarioLocked = false;
        }

        keyPressed = (int)gameConfig::eKeys::NONE; // Reset the input
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
    clrsrc();
    gotoxy(40, 10);
    std::cout << "oh no u lose a life oh no";
    Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
}

void Game::win()
{
    Map winScreen;
    winScreen.win();
}
void Game::lose()
{
    Map loseScreen;
    loseScreen.lose();
}



