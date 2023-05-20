#include "Board.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
COORD CursorPosition;

void gotoXY(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

Board::Board(int w, int h){
    this->width = w;
    this->height = h;
    GetConsoleScreenBufferInfo(console, &csbi);
    this->columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    this->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int Board::getWidth(){
    return this->width;
}

int Board::getHeight(){
    return this->height;
}

int Board::getCols(){
    return this->columns;
}

int Board::getRows(){
    return this->rows;
}

void Board::drawBoard(int width, int height){
    gotoXY((this->columns - width)/2 + 1, (this->rows - 3 - height)/2 - 1);
    for(int i = 0; i < width; i++) printf("_");
    gotoXY((this->columns - width)/2 + 1, (this->rows - 3 - height)/2 + height);
    for(int i = 0; i < width; i++) printf("-");
    for(int i = (this->rows - 3 - height)/2; i < (this->rows - 3 - height)/2 + height; i++) {
        gotoXY((this->columns - width)/2, i);
        printf("|");
    }
    for(int i = (this->rows - 3 - height)/2; i < (this->rows - 3 - height)/2 + height; i++) {
        gotoXY((this->columns - width)/2 + 1 + width, i);
        printf("|");
    }
}

Point::Point(int x, int y){
    this->x = x;
    this->y = y;
    this->next = nullptr;
}

void Point::setX(int x){
    this->x = x;
    //this->x %= width;
}

void Point::setY(int y){
    this->y = y;
    //this->y %= height;
}

int Point::getX(){
    return this->x;
}

int Point::getY(){
    return this->y;
}

void Point::draw(char c){
    gotoXY(this->x, this->y);
    printf("%c", int(c));
}

Point* Point::getNext(){
    return this->next;
}

void Point::setNext(Point* next){
    this->next = next;
}

void Point::erase(){
    gotoXY(this->x, this->y);
    printf(" ");
}

Point::~Point(){
    this->x = this->y = 0;
    this->next = NULL;
}