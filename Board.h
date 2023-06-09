#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include <Windows.h>

void gotoXY(int x, int y); 

class Board{
private:
    int width, height, columns, rows;
public:
    Board(int w, int h);
    void drawBoard(int width, int height);
    int getWidth();
    int getHeight();
    int getCols();
    int getRows();
    ~Board();
};

class Point{
private:
    int x, y;
    Point* next;
public:
    Point(int x = 0, int y = 0);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    void draw(char c);
    Point* getNext();
    void setNext(Point* next);
    void erase();
    ~Point();
};

#endif