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
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstring>




char Map::chooseScreens(std::vector<std::string> vec_to_fill)
{
    clrsrc();
    gotoxy(0, 0);
    std::cout << "choose screen to start with:\n";
    int num = 1;
    for (auto& it : vec_to_fill)
    {
        std::cout << num << "." << it << "\n";
        num++;
    }
    char key;
    while (true)
        if (_kbhit()){
             key = _getch();
			 if (key >= '1' && key <= '9')
                 return key;
}
    

    
}

void Map::printLegend(int remainingLives)
{
	Point  LegendPosition = getLegendPosition();
    gotoxy(LegendPosition.getX(), LegendPosition.getY());
    std::cout << "REMAINING LIVES: ";
   // gotoxy(LegendPosition.getX() + 4, LegendPosition.getY() + 1);
    for (int i = 0; i < remainingLives; i++)
        std::cout << "*";
    gotoxy(LegendPosition.getX(), LegendPosition.getY()+1);
    std::cout << "TIME PASSED: ";
    gotoxy(LegendPosition.getX(), LegendPosition.getY() + 2);
    std::cout << "SCORE: ";


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
int Map::mainMenu(std::vector<std::string> vec_to_fill)
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
            char key = chooseScreens(vec_to_fill);
            clrsrc();
            return key;
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
        "                                                                               ", // 25
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
       "                                                                               ", // 25
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

void Map::printClock(int& secondsElapsed)
{
}



int Map::load(const std::string& filename) {
    std::ifstream screen_file(filename);
    if (!screen_file.is_open()) {
        throw std::runtime_error("Failed to open the file: " + filename);
    }

    int curr_row = 0;
    int curr_col = 0;
    char c;

    bool foundMario = false;
    bool foundPauline = false;
    bool foundDonkey = false;
    bool foundLegend = false;
	bool isQCurrRow = false;
    std::vector<Point> ghostStartPositions;

   
    while (!screen_file.get(c).eof()) {
        if (c == '\n') {
            if (curr_col < Map::GAME_WIDTH && !isQCurrRow) 
                   for (; curr_col < Map::GAME_WIDTH-2; ++curr_col) 
                       originalMap[curr_row][curr_col] = ' ';   // Fill the remaining space with ' ' (spaces)
            
            else if (curr_col > Map::GAME_WIDTH) {
				//not good return with a proper message and ignore the screen
            }
            //originalMap[curr_row][++curr_col] = '\0';
          
            ++curr_row;
            curr_col = 0;
            if (curr_row > Map::GAME_HEIGHT) {
                throw std::runtime_error("Number of rows exceeds maximum height: " + std::to_string(Map::GAME_HEIGHT));
            }
			
            continue;
        }

        if (curr_col < Map::GAME_WIDTH && curr_row < Map::GAME_HEIGHT) {
            switch (c) {
            case '@':  // Mario
                if (foundMario) { originalMap[curr_row][curr_col++] = ' '; break; } //from the second mario (if there is), ignore him

                foundMario = true;
                marioStartPos = { curr_col, curr_row };
                originalMap[curr_row][curr_col++] = ' ';  // Replace with space
                break;

            case '$':  // Pauline
                if (foundPauline) { originalMap[curr_row][curr_col++] = ' '; break; }//from the second Pauline (if there is), ignore her
               
                foundPauline = true;
                originalMap[curr_row][curr_col++] = '$';
                break;

            case '&':  // Donkey Kong
				if (foundDonkey) { originalMap[curr_row][curr_col++] = ' '; break; }//from the second Donkey Kong (if there is), ignore him
                foundDonkey = true;
                barrelStartPoint = { curr_col, curr_row + 1 };
                originalMap[curr_row][curr_col++] = '&';
                break;

            case 'x':  // Ghost
                ghostStartPositions.emplace_back(curr_col, curr_row);
                originalMap[curr_row][curr_col++] = ' ';  // Replace with space
                break;

            case 'L':  // Legend
                if (foundLegend) {
                    originalMap[curr_row][curr_col++] = ' '; break;  }//from the second Legend (if there is), ignore it 
                foundLegend = true;
                legendPosition = { curr_col, curr_row };
                originalMap[curr_row][curr_col++] = ' ';  // Replace with space
                break;

            case 'p':  // Patish
                patishPosition = { curr_col, curr_row };
                originalMap[curr_row][curr_col++] = 'p';  
                break;

            case 'Q':  // border
                originalMap[curr_row][curr_col++] = 'Q';
				isQCurrRow = true;
                break;

            default:
                originalMap[curr_row][curr_col++] = c;  // Regular character
                break;
            }
        }
        
    }
    
	originalMap[curr_row][curr_col] = '\0';  // Null-terminate the last row



    if (!foundMario) { return 1; } // not good, return int, a proper message, and ignore the screen 
    if (!foundPauline) { return 2; } //not good, return int, a proper message, and ignore the screen 
    if (!foundDonkey) { return 3; } // not good, return int, a proper message, and ignore the screen 
    if (!foundLegend) { return 4; } // not good, return int, a proper message, and ignore the screen 

    
    this->ghostStartPositions = ghostStartPositions;  // Update ghost positions in the class
    return -1;
}

