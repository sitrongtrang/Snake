#ifndef _GAME_H_
#define _GAME_H_

#include "Board.h"
#include "Snake.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <algorithm>
#include <vector>

class Game{
private:
    Snake* snake;
    Point* food;
    Board* board;
    bool** location;
public:
    Game();
    void foodLocation();
    bool update();
    void resetLocation();
    void startGame();
    void playGame();
    void resetGame();
    void runGame();
    ~Game();
};

#endif