#include "Game.h"

Game::Game(){
    this->food = nullptr;
    this->board = new Board(20, 20);
    this->snake = new Snake(this->board->getCols(), this->board->getRows());
    this->location = new bool*[this->board->getRows()];
    for (int i = 0; i < this->board->getRows(); i++){
        (this->location)[i] = new bool [this->board->getCols()];
        for (int j = 0; j < this->board->getCols(); j++){
            (this->location)[i][j] = false;
        }
    }
}

void Game::foodLocation(){
    if (this->food) {
        this->food->erase();
        delete this->food;
    }

    std::vector<int> empty;
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            if (!location[i][j]) empty.push_back(i*20+j);
        }
    }

    int index = rand() % empty.size();

    int x = empty[index] / 20;
    int y = empty[index] % 20;
    
    this->food = new Point(x + (this->board->getCols()- this->board->getWidth())/2 + 1, 
                            y + (this->board->getRows() - 3 - this->board->getHeight())/2);
    this->food->draw('o');
}

bool Game::update() {
    if (!this->food) this->foodLocation();
    this->snake->move(this->board->getWidth(), this->board->getHeight(), this->board->getCols(), this->board->getRows(), this->location);
    if (this->snake->eatFood(this->food)) {
        this->snake->setScore(this->snake->getScore()+1);
        this->food->erase();
        delete this->food;
        this->food = nullptr;
        this->snake->getLonger(this->board->getWidth(), this->board->getHeight(), this->board->getCols(), this->board->getRows(), this->location);
    }
    this->snake->drawSnake();
    return this->snake->dead();
}

void Game::resetLocation(){
    for (int i = 0; i < this->board->getRows(); i++){
        for (int j = 0; j < this->board->getCols(); j++){
            (this->location)[i][j] = false;
        }
    }
}

void Game::startGame(){
    system("cls");
    this->board->drawBoard(100, 15);
    this->resetLocation();
    gotoXY(15, 7);
    printf("Developer: Trang Si Trong");
    gotoXY(15, 8);
    printf("Student's Id: 2110621");
    gotoXY(50, 10);
    printf("-------SNAKE-------");
    gotoXY(17, 13);
    printf("Press Enter to start game.");
    gotoXY(17, 14);
    printf("Press Space to pause when playing.");
    gotoXY(17, 15);
    printf("Press Esc to quit game.");
    gotoXY(0, 23);
}

void Game::playGame(){
    srand(time(NULL)); 
    system("cls");
    this->board->drawBoard(20, 20);
    this->resetLocation();
    while(true) {
        if(kbhit()) {
            char c = getch();
            if(c == 32) {
                this->snake->drawSnake();
                gotoXY(45, 28);
                system("Pause");
                gotoXY(45, 28);
                for (int i = 0; i < 70; i++){
                    printf(" ");
                }
                this->snake->eraseSnake();
            }
            if(c == 72) this->snake->changeDir(0, -1);
            if(c == 80) this->snake->changeDir(0, 1);
            if(c == 77) this->snake->changeDir(1, 0);
            if(c == 75) this->snake->changeDir(-1, 0);
            if(c == 27) break;
        }
        bool gameOver = this->update();
        this->snake->printScore();
        int reduceTime = (this->snake->getScore()/3 < 100) ? this->snake->getScore() : 100;
        Sleep(140 - reduceTime);
        if(gameOver) break;
        this->snake->eraseSnake();
    }
}

void Game::resetGame(){
    delete this->snake;
    delete this->food;
    this->food = nullptr;
    this->snake = new Snake(this->board->getCols(), this->board->getRows());
    this->board = new Board(20, 20);
    this->resetLocation();
}

void Game::runGame(){
    int highscore = 0;
    while(true) {
        bool quitGame = false;
        this->startGame();
        while(true) {
            if(kbhit()) {
                char c = getch();
                if(c == '\r') {
                    this->playGame();
                    break;
                } else if(c == 27) {
                    quitGame = true;
                    break;
                }
            }
        }
        system("cls");
        if(quitGame) break;
        highscore = (highscore > this->snake->getScore()) ? highscore : this->snake->getScore();
        this->board->drawBoard(100, 15);
        gotoXY(15, 7);
        printf("Developer: Trang Si Trong");
        gotoXY(15, 8);
        printf("Student's Id: 2110621");
        gotoXY(55, 10);
        printf("Highscore: %d", highscore);
        gotoXY(55, 11);
        printf("Your Score: %d", this->snake->getScore());
        gotoXY(15, 13);
        printf("Press r or R to retry.");
        while(true) {
            char c = getch();
            if(c == 'r' || c == 'R') {
                this->resetGame();
                break;
            }
        }
    }
}

Game::~Game(){
    delete this->snake;
    if (this->food) delete this->food;
    for (int i = 0; i < this->board->getRows(); i++){
        delete [] this->location[i];
    }
    delete [] this->location;
    delete this->board;
}