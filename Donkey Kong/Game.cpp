#include <iostream>
#include "Game.h"
#include "gameConfig.h"
#include <conio.h> //for kbhit_ getch
#include <ctime>  // For time functions
#include <cstdlib>  // For rand() and srand()
#include <Windows.h>
#include "Barrel.h"
#include "Map.h"
#include "Mario.h"
#include "Point.h"
#include <chrono>
#include <vector>

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

int Game::startGame() {
    ShowConsoleCursor(false);

    std::vector<Barrel> barrels; 
    int barrelCurr = 0; 
    int barrelSpawnCounter = 0;
    Point explosionPos;
    Map gameBoard;
    gameBoard.printcurrentMap();
    Mario mario(&gameBoard);

    int currLives = (int)gameConfig::Size::START_LIVES;
    gameBoard.printRemainingLives(currLives);

    char keyPressed = (char)(gameConfig::eKeys::STAY);
    bool isMarioLocked = false;

    auto lastToggleTime = std::chrono::steady_clock::now();

    std::vector<Point> togglePoints = defineFloorsToToggle(gameBoard);

    std::vector<Ghost> ghosts;
    spawnGhosts(ghosts, gameBoard);

    while (true) {
        keyPressed = (int)gameConfig::eKeys::NONE;

        if (_kbhit()) {
            keyPressed = std::tolower(_getch());

            if (keyPressed == (int)gameConfig::eKeys::ESC) {
                pause();
                gameBoard.printcurrentMap();
            }
        }

        barrelSpawnCounter++;
        if (handleLifeLoss(currLives, mario, gameBoard, barrelCurr, barrelSpawnCounter, isMarioLocked, ghosts, barrels)) {
            return -1;
        }

        if (mario.isNearPaulina()) {
            return 1;
        }

        if (mario.isNearPatish() && keyPressed == (char)gameConfig::eKeys::PATISH) {
            mario.isWithPatish = true;
            gameBoard.currentMap[23][49] = ' '; //HARD CODED CHANGE!!!!!!
        }
        
        drawMario(mario);
        

        if (barrelSpawnCounter == (int)gameConfig::Size::BARRREL_COUNTER && barrelCurr < (int)gameConfig::Size::BARREL_MAX) {
            spawnBarrel(barrels, barrelCurr, gameBoard); 
            barrelSpawnCounter = 0;
        }
        
        


        moveBarrels(barrels, barrelCurr, mario); 
        moveGhosts(ghosts);

        // Chat-GPT Code
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastToggleTime).count() >= 4) {
            for (const Point& p : togglePoints) {
                toggleArrow(gameBoard, p);
            }

            lastToggleTime = currentTime;
        }


        Sleep((int)gameConfig::Sleep::GAME_LOOP_SLEEP);

        if (isMarioLocked) {
            handleMarioLocked(keyPressed, mario, isMarioLocked);
        }
        else {
            mario.move((gameConfig::eKeys)keyPressed);
            isMarioLocked = isMarioInLongAction(mario);
        }

        if (isMarioInShortAction(mario)) {
            isMarioLocked = false;
        }

        keyPressed = (int)gameConfig::eKeys::NONE;
    }

    return 0;
}

//    OUR impement for the function CHAT-GPT suggested
void Game::toggleArrow(Map& gameBoard, const Point& point) {
;
		std::cout << '<';    char currentChar = gameBoard.currentMap[point.getY()][point.getX()];
    if (currentChar == '>') {
		gameBoard.currentMap[point.getY()][point.getX()] = '<';
        gotoxy(point.getX(), point.getY());
    }
    else  if (currentChar == '<') {
        gameBoard.currentMap[point.getY()][point.getX()] = '>';
        gotoxy(point.getX(), point.getY());
        std::cout << '>';
    }
}


void Game::drawMario(Mario& mario) {
    char curr = mario.getMapChar();
    mario.draw(curr == 'H' ? '#' : '@');
}

bool Game::handleLifeLoss(int& currLives, Mario& mario, Map& gameBoard, int& barrelCurr, int& barrelSpawnCounter, bool& isMarioLocked, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels) {
    if (currLives == mario.lives) return false;

    if (currLives == 1) return true;

    loseALife();
    gameBoard.resetMap();
    gameBoard.printcurrentMap();
    currLives--;
    gameBoard.printRemainingLives(currLives);
    mario.resetMario();
    resetGhosts(ghosts);
    barrelCurr = 0;
    barrelSpawnCounter = 0;
    isMarioLocked = false;
    barrels.clear();

    return false;
}

void Game::spawnBarrel(std::vector<Barrel>& barrels, int& barrelCurr, Map& gameBoard) {
    barrels.push_back(Barrel(&gameBoard));  // Add to vector instead of using array index
    barrelCurr++;
}

void Game::moveBarrels(std::vector<Barrel>& barrels, int barrelCurr, Mario& mario) {
    for (int i = 0; i < barrelCurr; i++) {
        char curr = barrels[i].getMapChar();
        barrels[i].draw('O');
        barrels[i].move(&mario);
    }
}

void Game::handleMarioLocked(char keyPressed, Mario& mario, bool& isMarioLocked) {
    if (keyPressed == (char)gameConfig::eKeys::STAY &&
        (mario.state == Mario::State::CLIMBING_UP || mario.state == Mario::State::CLIMBING_DOWN)) {
        mario.state = Mario::State::STANDING;
        isMarioLocked = false;
    }
    else {
        mario.move();
    }
}

bool Game::isMarioInLongAction(Mario& mario) {
    return mario.state == Mario::State::JUMPING ||
        mario.state == Mario::State::CLIMBING_UP ||
        mario.state == Mario::State::CLIMBING_DOWN;
}

bool Game::isMarioInShortAction(Mario& mario) {
    return mario.state == Mario::State::STANDING ||
        mario.state == Mario::State::WALKING;
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

//פונקציה זמנית לבדיקת הרוחות
void Game::spawnGhosts(std::vector<Ghost>& ghosts, Map& gameBoard) {
    ghosts.emplace_back(&gameBoard, Point(50, 18), std::rand());
    ghosts.emplace_back(&gameBoard, Point(50, 15), std::rand());
    ghosts.emplace_back(&gameBoard, Point(40, 15), std::rand());
    ghosts.emplace_back(&gameBoard, Point(50, 12), std::rand());
    ghosts.emplace_back(&gameBoard, Point(60, 12), std::rand());
}

void Game::moveGhosts(std::vector<Ghost>& ghosts) {
    for (auto& ghost : ghosts) {
        ghost.move(ghosts);
    }
}

void Game::resetGhosts(std::vector<Ghost>& ghosts) {
    for (auto& ghost : ghosts) {
        ghost.reset(); 
    }
}

std::vector<Point> Game::defineFloorsToToggle(Map& map)
{
    std::vector<Point> res;
    for(int i=0; i< gameConfig::GAME_HEIGHT; i++)
        for (int j = 0; j < gameConfig::GAME_WIDTH; j++)
        {
            if ((map.originalMap[i][j] == '<' && map.originalMap[i][j - 1] == '=' && map.originalMap[i][j + 1] == '=') ||
                (map.originalMap[i][j] == '>' && map.originalMap[i][j - 1] == '=' && map.originalMap[i][j + 1] == '='))
            {
                Point p(j, i);
                res.push_back(p);
            }
               
        }
    return res;
}

void Game::patishDestroy(std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts, Mario& mario, char key) {
    if (mario.isGhostHere() && key == (char)gameConfig::eKeys::PATISH && mario.isWithPatish) {
        ;
    }
    if (mario.isBarrelHere() && key == (char)gameConfig::eKeys::PATISH && mario.isWithPatish) {
        ;
    }
}




