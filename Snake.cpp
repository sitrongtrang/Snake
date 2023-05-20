#include "Snake.h"

Snake::Snake(int cols, int rows){
    Point* p = new Point(cols/2, rows/2);
    this->head = this->tail = p;
    this->xspeed = 1;
    this->yspeed = 0;
    this->score = 0;
}

void Snake::drawSnake(){
    Point* body = this->head;
    body->draw('O');
    while (body->getNext()){
        body = body->getNext();
        body->draw('*');
    }
}

void Snake::move(int width, int height, int cols, int rows, bool** location){
    location[this->tail->getX() - (cols - width)/2 - 1][this->tail->getY() - (rows - 3 - height)/2] = false;
    Point* body = this->head;
    int x = body->getX();
    int y = body->getY();
    while (body->getNext()){
        int nextX = body->getNext()->getX();
        int nextY = body->getNext()->getY();
        body->getNext()->setX(x);
        body->getNext()->setY(y);
        x = nextX;
        y = nextY;
        body = body->getNext();
    }
    this->head->setX(this->head->getX() + xspeed);
    this->head->setY(this->head->getY() + yspeed);
    if (this->head->getY() < (rows - 3 - height)/2) this->head->setY(height + (rows - 3 - height)/2 - 1);
    if (this->head->getY() > height + (rows - 3 - height)/2 - 1) this->head->setY((rows - 3 - height)/2);
    if (this->head->getX() < (cols - width)/2 + 1) this->head->setX(width + (cols - width)/2);
    if (this->head->getX() > width + (cols - width)/2) this->head->setX((cols - width)/2 + 1);
    location[this->head->getX() - (cols - width)/2 - 1][this->head->getY() - (rows - 3 - height)/2] = true;   
}

void Snake::changeDir(int x, int y){
    if (x == -this->xspeed && y == -this->yspeed) return;
    this->xspeed = x;
    this->yspeed = y;
}

bool Snake::eatFood(Point* food){
    return this->head->getX() == food->getX() && this->head->getY()== food->getY();
}

void Snake::getLonger(int width, int height, int cols, int rows, bool** location){
    Point* temp = new Point(this->tail->getX(), this->tail->getY());
    this->move(width, height, cols, rows, location);
    this->tail->setNext(temp);
    this->tail = temp;
    location[this->tail->getX() - (cols - width)/2 - 1][this->tail->getY() - (rows - 3 - height)/2] = true;
}

int Snake::getScore(){
    return this->score;
}

void Snake::setScore(int n){
    this->score = n;
}

void Snake::printScore() {
    gotoXY(90, 3);
    printf("Score: %d", this->score);
}

void Snake::eraseSnake(){
    Point* temp = this->head;
    while (temp){
        temp->erase();
        temp = temp->getNext();
    }
}

bool Snake::dead(){
    int headX = this->head->getX();
    int headY = this->head->getY();
    Point* temp = this->head->getNext();
    while (temp){
        if (temp->getX() == headX && temp->getY() == head->getY()) return true;
        temp = temp->getNext();
    }
    return false;
}

Snake::~Snake(){
    Point* body = this->head;
    while (body){
        Point* temp = body->getNext();
        delete body;
        body = temp;
    }
    this->score = this->xspeed = this->yspeed = 0;
}