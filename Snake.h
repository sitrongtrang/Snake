#ifndef _SNAKE_H_
#define _SNAKE_H_
#include "Board.h"

class Snake{
private:
    Point* head, *tail;
    int xspeed, yspeed, score;
public:
    Snake(int cols, int rows);
    void drawSnake();
    void move(int width, int height, int cols, int rows, bool** location);
    void changeDir(int x, int y);
    bool eatFood(Point* food);
    void getLonger(int width, int height, int cols, int rows, bool** location);
    int getScore();
    void setScore(int n);
    void printScore();
    void eraseSnake();
    bool dead();
    ~Snake();
};

#endif 