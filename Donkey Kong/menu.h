#pragma once
#include "gameConfig.h"

class menu
{
public:
    const char loginScreen[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH] = {
        "                                                                               ", // 1
        "                              ======================                           ", // 2
        "                              Welcome to Donkey Kong                           ", // 3
        "                              ======================                           ", // 4
        "                                           -=-                                 ", // 5
        "                                -=       =##*-                                 ", // 6
        "                                -=      -*****#+-                              ", // 7
        "                                -+*-    =   --=+*+==-                          ", // 8
        "                             --=**#%*=++== =-=***@%###*-                       ", // 9
        "                              -=+*%@@@%*      -=*@%####+                       ", // 10
        "                               -+#@@@@@*---====+#@#####+                       ", // 11
        "                               -*%%@@@@@+----=+*#%%#####-                      ", // 12
        "                                   ---   -*#***##%%#####-                      ", // 13
        "                                       =*#@%*#%###%###%#-                      ", // 14
        "                                    -====#%%#+*####%#%%%#                      ", // 15
        "                                    =+++=*%%%+**#####%%#-                      ", // 16
        "                                         -=**+    -=*#*+=-                     ", // 17
        "                                          ---  ------==+*+++-                  ", // 18
        "                                               -===-                           ", // 19
        "                           press the following keys to:                        ", // 20
        "                               1. Start Game                                   ", // 21
        "                               8. Show instructions                            ", // 22
        "                               9. Exit                                         ", // 23
        "                               0. A special surprise                           ", // 24
        "===============================================================================", // 25

    };

    const char instructionsScreen[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH] = {
        "                                                                               ", // 1
        "                                                                               ", // 2
        "                                                                               ", // 3
        "                                                                               ", // 4
        "                                                                               ", // 5
        "                              ======================                           ", // 6
        "                                 Game Instructions                             ", // 7
        "                              ======================                           ", // 8
        "                                                                               ", // 9
        "                     1. Use A (left), W (up), D (right), X (down),             ", // 10
        "                            S (stand) keys to move Mario.                      ", // 11
        "                                                                               ", // 12
        "                                2. Avoid barrels.                              ", // 13
        "                                                                               ", // 14
        "                         3. Reach to the princess to win!                      ", // 15
        "                                                                               ", // 16
        "                                   4. Have fun!                                ", // 17
        "                                                                               ", // 18
        "                     Press the ESC key to return to the main menu...           ", // 19
        "                                                                               ", // 20
        "                                                                               ", // 21
        "                                                                               ", // 22
        "                                                                               ", // 23
        "                                                                               ", // 24
        "===============================================================================", // 25

    };
    int mainMenu();
    void showMenu();
    void showInstructions();
    int exitGame();
    void win();
    void lose();

};
