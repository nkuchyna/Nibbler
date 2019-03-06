//
// Created by Nadiia KUCHYNA on 2019-01-19.
//
#include "RandomObjGenerator.h"
#include "ErrorException.h"

RandomObjGenerator::RandomObjGenerator(){}
RandomObjGenerator::RandomObjGenerator(std::vector<Particle *> *_obstacles, std::vector<Particle *> *_apples, int w, int h){
    this->_width  =w;
    this->_height = h;
    this->_obstacles = _obstacles;
    this->_apples = _apples;
    this->countOfObstacles = 1;
}
RandomObjGenerator::~RandomObjGenerator(){}

RandomObjGenerator::RandomObjGenerator(RandomObjGenerator const &src) {
    *this = src;
    return;
}

RandomObjGenerator & RandomObjGenerator::operator=(const RandomObjGenerator &src) {
    this->_obstacles = src.getObstacles();
    this->_apples = src.getApples();
    return *this;
}

std::vector<Particle *> * RandomObjGenerator::getObstacles() const{
    return this->_obstacles;
}

std::vector<Particle *> * RandomObjGenerator::getApples() const{
    return this->_apples;
}
clock_t RandomObjGenerator::getClockSA()
{
    return this->clockSuperApple;
}



void RandomObjGenerator::setObstacles( std::vector<Particle *> *ob){
    this->_obstacles = ob;
}
void RandomObjGenerator::setApples(std::vector<Particle *> * app){
    this->_apples = app;
}
void RandomObjGenerator::setClockSA(clock_t t)
{
    this->clockSuperApple = t;
}

void  RandomObjGenerator::generateObstacle()
{
    int x  = rand() %  this->_width / 3 ;
    int y = rand() % this->_height / 3;
    if (countOfObstacles % 2 == 0)
        x = x + this->_width/2;
    else if (countOfObstacles % 5 == 0) {
        x = x + this->_width / 2;
        y = y + this->_height  / 2;
    }
    else if (countOfObstacles % 3 == 0)
        y = y + this->_height / 2;
    else
        ;
    if (rand() % 2 == 0)
    {
        this->_obstacles->push_back(new Particle(x , y, OBSTACLE));
        this->_obstacles->push_back(new Particle(x + 1 , y, OBSTACLE));
        this->_obstacles->push_back(new Particle(x + 2, y, OBSTACLE));
    }
    else{
        this->_obstacles->push_back(new Particle(x , y, OBSTACLE));
        this->_obstacles->push_back(new Particle(x  , y + 1, OBSTACLE));
        this->_obstacles->push_back(new Particle(x , y + 2, OBSTACLE));
    }

    for (int i = 0; i < this->_width; i++)
    {
        this->_obstacles->push_back(new Particle(i , 0, FRAME));
        this->_obstacles->push_back(new Particle(i , this->_height - 1, FRAME));
    }
    for (int i = 0; i < this->_height; i++)
    {
        this->_obstacles->push_back(new Particle(0 , i, FRAME));
        this->_obstacles->push_back(new Particle( this->_width - 1,i, FRAME));
    }
    countOfObstacles++;
}

void RandomObjGenerator::generateApple()
{
    superA++;
    int xS = 0;
    int yS = 0;
    int x = 0;
    int y = 0;
    if (superA % 5 == 0) {
         xS = rand() % this->_width;
         yS = rand() % this->_height;
    }
    try {
        do {
            x = rand() % this->_width;
            y = rand() % this->_height;
            _apples->push_back(new Particle(x, y, APPLE));
            if (superA % 5 == 0) {
                _apples->push_back(new Particle(xS, yS, SUPER_APPLE));
                clockSuperApple = clock();
            }
        } while (checkObstacles(x, y));
    }
    catch (std::bad_alloc& ba)
    {
        throw (new ErrorException("The memory was not allocated for apples"));
    }
}

bool RandomObjGenerator::checkObstacles(int x, int y)
{
    for (auto& it : *this->_obstacles)
    {
        if (it->getX() == x && it->getY() == y)
            return true;
    }
    return false;
}

void RandomObjGenerator::refreshObstacles(int difficulty)
{
    for (auto &it : *this->_obstacles)
        delete it;
    this->_obstacles->clear();
    try {
        for (int i = 0; i < difficulty; i++)
            this->generateObstacle();
    }
    catch (std::bad_alloc& ba)
    {
        throw (new ErrorException("The memory was not allocated for obstacles"));
    }
}

void RandomObjGenerator::refreshApples()
{
    for( auto& it: *this->_apples)
        delete it;
    this->_apples->clear();
    try {
        this->generateApple();
    }
    catch (std::bad_alloc& ba)
    {
        throw (new ErrorException("The memory was not allocated for apples"));
    }
}


