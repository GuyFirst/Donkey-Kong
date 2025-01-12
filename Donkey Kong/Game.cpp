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
#include <filesystem>
#include <algorithm>


void Game::run()
{
    std::vector<std::string> vec_to_fill;
    getAllBoardFileNames(vec_to_fill);

    int flag = 0;
    Point screenStart(0, 0);
    while (true)                                        //
    {                                                   //
        gotoxy(screenStart.getX(), screenStart.getY()); // 
        Map menu;                                       // the flags indicates if the player wins, loses, or quiting the game.
        flag = menu.mainMenu(vec_to_fill);                         //  -1 for deciding to quit (before we entered the game)
        if (flag == -1)                                 //   1 if the player won
            return;                                     //  -1 if the player lost
        flag = startGame(vec_to_fill, flag - 49);                             //
        if (flag == 1)                                  //
            win();                                      //
        else                                            //
            lose();
    }
    return;
}

void Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        auto filename = entry.path().filename();
        auto filenameStr = filename.string();
        if (filenameStr.substr(0, 5) == "dkong" && filename.extension() == ".screen") {
            std::cout << " ^ added!!\n";
            vec_to_fill.push_back(filenameStr);
        }
    }
    std::sort(vec_to_fill.begin(), vec_to_fill.end());
}

void Game::handleErrors(int& flag)
{
    clrsrc();
    switch (flag) {
    case 1:
        std::cout << "The provided file does not meet the game settings,\n as Mario does not appear in the file.";
        flag = 0;
        Sleep((int)gameConfig::Sleep::SCREEN_SLEEP * 2);
        break;
    case 2:
        std::cout << "The provided file does not meet the game settings,\nas Pauline dose not appear in the file and you can not win.";
        flag = 0;
        Sleep(((int)gameConfig::Sleep::SCREEN_SLEEP) * 3);
        break;
    case 3:
        std::cout << "The provided file does not meet the game settings,\nas Donkey does not appear in the file.";
        flag = 0;
        Sleep(((int)gameConfig::Sleep::SCREEN_SLEEP) * 3);
        break;
    case 4:
        std::cout << "The provided file does not meet the game settings,\nas the Legend must appear in the file.";
        flag = 0;
        Sleep(((int)gameConfig::Sleep::SCREEN_SLEEP) * 3);
        break;
    }

}


int Game::startGame(std::vector<std::string> fileNames, int index) {

    for (int i = index; i < fileNames.size(); i++)
    {
        ShowConsoleCursor(false);
        // Initialize game board
        Map gameBoard;
        int flag = gameBoard.load(fileNames[i]);
        handleErrors(flag);
        if (!flag)
            continue;
        gameBoard.resetMap();
        gameBoard.printcurrentMap();
        // Initialize Mario
        Mario mario(&gameBoard, gameBoard.getMarioStartPos());

        // Initialize barrels
        std::vector<Barrel> barrels;
        barrels.emplace_back(&gameBoard, gameBoard.getBarrelStartPoint());

        // Initialize ghosts
        std::vector<Ghost> ghosts;
        for (const Point& ghostPos : gameBoard.getGhostStartPositions()) {
            ghosts.emplace_back(&gameBoard, ghosts.size(), ghostPos);
        }


        // Game state variables
        int score = (int)gameConfig::Score::STARTING_SCORE;
        int currLives = (int)gameConfig::Size::START_LIVES;
        gameBoard.printLegend(currLives);

        char keyPressed;
        bool isMarioLocked = false;
        bool patishPicked = false;
        bool isGamePaused = false;

        auto lastToggleTime = std::chrono::steady_clock::now();


        // Toggle points for arrows
        std::vector<Point> togglePoints = defineFloorsToToggle(gameBoard);


        while (true) {
            keyPressed = (int)gameConfig::eKeys::NONE;

            // Handle user input
            if (_kbhit()) {
                keyPressed = std::tolower(_getch());
                if (keyPressed == (int)gameConfig::eKeys::ESC) {
                    pause();
                    gameBoard.printcurrentMap();
                    gameBoard.printLegend(currLives);
                }
            }

            // Handle Mario's interaction with Patish
            if (mario.isNearPatish() && !patishPicked) {
                mario.isWithPatish = true;
                patishPicked = true;
                Point hammerPos = gameBoard.getPatishPosition();
                gameBoard.currentMap[hammerPos.getY()][hammerPos.getX()] = ' '; // Remove patish from irignal and current
                gameBoard.originalMap[hammerPos.getY()][hammerPos.getX()] = ' ';
            }
            // Handle life loss
            if (handleLifeLoss(currLives, mario, gameBoard, Barrel::barrelCurr, Barrel::barrelSpawnCounter, isMarioLocked, ghosts, barrels, score)) {
                return -1;
            }

            // Check if Mario reached Pauline
            if (mario.isNearPaulina()) {
                break;
            }

            // Handle barrel spawning
            Barrel::barrelSpawnCounter++;
            if (Barrel::barrelSpawnCounter == (int)gameConfig::Size::BARRREL_COUNTER && Barrel::barrelCurr < (int)gameConfig::Size::BARREL_MAX) {
                barrels.emplace_back(&gameBoard, gameBoard.getBarrelStartPoint());
                Barrel::resetBarrelSpawnCounter();
                Barrel::incrementBarrelCurr();  // Increment the static barrel counter
            }

            // Move barrels and ghosts
            moveBarrels(barrels, mario);
            moveGhosts(ghosts);

            // Destroy barrels or ghosts if Patish is used
            patishDestroy(barrels, ghosts, mario, keyPressed);

            // Toggle arrows on map
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastToggleTime).count() >= 4) {
                for (const Point& p : togglePoints) {
                    toggleArrow(gameBoard, p);
                }
                lastToggleTime = now;
            }

            // Sleep to control game speed
            Sleep((int)gameConfig::Sleep::GAME_LOOP_SLEEP);

            // Handle Mario movement
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

            Point LegendPosition = gameBoard.getLegendPosition();
            // Display updated score
            gotoxy(LegendPosition.getX() + 7, LegendPosition.getY() + 2);
            std::cout << score;


        }

        //here implement a screen that says you finished the i'th screen
    }
    return 1;
}





//    OUR impement for the function CHAT-GPT suggested
void Game::toggleArrow(Map& gameBoard, const Point& point) {
    ;
    char currentChar = gameBoard.currentMap[point.getY()][point.getX()];
    if (currentChar == '>') {
        gameBoard.currentMap[point.getY()][point.getX()] = '<';
        gotoxy(point.getX(), point.getY());
        std::cout << '<';
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

bool Game::handleLifeLoss(int& currLives, Mario& mario, Map& gameBoard, int& barrelCurr, int& barrelSpawnCounter, bool& isMarioLocked, std::vector<Ghost>& ghosts, std::vector<Barrel>& barrels, int& score) {
    if (currLives == mario.lives) return false;

    if (currLives == 1) return true;
    score -= (int)gameConfig::Score::LIFE_LOSS;
    loseALife();
    gameBoard.resetMap();
    gameBoard.printcurrentMap();
    currLives--;
    gameBoard.printLegend(currLives);
    mario.resetMario();
    resetGhosts(ghosts);
    barrelCurr = 0;
    barrelSpawnCounter = 0;
    isMarioLocked = false;
    barrels.clear();

    return false;
}

void Game::spawnBarrel(std::vector<Barrel>& barrels, int& barrelCurr, Map& gameBoard) {
    barrels.push_back(Barrel(&gameBoard, gameBoard.getBarrelStartPoint()));  // Add to vector instead of using array index
    barrelCurr++;
}

void Game::moveBarrels(std::vector<Barrel>& barrels, Mario& mario) {
    for (int i = 0; i < Barrel::barrelCurr; i++) {
        if (i < barrels.size()) {
            char curr = barrels[i].getMapChar();
            barrels[i].draw('O');
            barrels[i].move(barrels, &mario);
        }
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

bool Game::isMarioInLongAction(Mario& mario) const {
    return mario.state == Mario::State::JUMPING ||
        mario.state == Mario::State::CLIMBING_UP ||
        mario.state == Mario::State::CLIMBING_DOWN;
}

bool Game::isMarioInShortAction(Mario& mario) const {
    return mario.state == Mario::State::STANDING ||
        mario.state == Mario::State::WALKING;
}


void Game::pause()
{
    clrsrc();
    gotoxy(20, 10);
    std::cout << "Game paused, press ESC again to continue.";
    gotoxy(20, 12);
    std::cout << "But it is not mandatory to present such a message.";


    char keyPressed = 0;
    while (true) {
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (char)gameConfig::eKeys::ESC) {
                // When ESC is pressed, unpause the game
                clrsrc();
                gotoxy(0, 0);
                return;
            }
        }
    }
}





void Game::loseALife() const
{
    clrsrc();
    gotoxy(40, 10);
    std::cout << "oh no u lose a life oh no";
    Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
}

void Game::win() const
{
    Map winScreen;
    winScreen.win();
}
void Game::lose() const
{
    Map loseScreen;
    loseScreen.lose();
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
    for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
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
    if (key == (char)gameConfig::eKeys::PATISH && mario.isWithPatish) {
        Point marioPos1 = mario.getPoint();
        Point marioPos2 = mario.getPoint();
        marioPos1.setX(marioPos1.getX() + 1);
        marioPos2.setX(marioPos1.getX() - 1);
        for (auto it = ghosts.begin(); it != ghosts.end(); ) {
            if (it->getPoint() == mario.getPoint() || it->getPoint() == marioPos1 || it->getPoint() == marioPos2) {
                it->draw(' ');
                it = ghosts.erase(it);
            }
            else {
                ++it;
            }
        }
        for (auto it = barrels.begin(); it != barrels.end(); ) {
            if (it->getPoint() == mario.getPoint() || it->getPoint() == marioPos1 || it->getPoint() == marioPos2) {
                it->draw(' ');
                it = barrels.erase(it);
                Barrel::barrelCurr--;
            }
            else {
                ++it;
            }
        }

    }
}

void Game::updateClock(const std::chrono::seconds& elapsedTime)
{
    // Calculate minutes and seconds from total elapsed seconds
    int secondsElapsed = elapsedTime.count();
    int minutes = secondsElapsed / 60;
    int seconds = secondsElapsed % 60;


    // Print the clock with zero padding (e.g., 01:05 for 1 minute and 5 seconds)
    std::cout << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
}

