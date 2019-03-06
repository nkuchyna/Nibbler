//
// Created by Vyachealav MARTYNUIK on 2019-01-11.
//

#ifndef NIBBLER_SNAKE_H
#define NIBBLER_SNAKE_H
#include "Particle.h"
#include "IRender.h"

class Snake {

public:
    Snake();
    Snake(Snake const &);
    Snake const &operator=(Snake const &);
    ~Snake();

    std::vector <Particle *> &getSnake();
    int                      getHealth();
    void setHealth(int);
    eDirection getDir();
    void setDir(eDirection);

    eTurn whereTo();
    bool checkObstacles(int x, int y, std::vector<Particle *>obsticles);
    void startSnake(int, int);
    void move();

    void refreshSnake();
    eCollideType collide(std::vector<Particle *> *, std::vector<Particle *>);

private:

    int _mapWidth;
    int _mapHeight;
    bool oppositeDir(eDirection now, eDirection next);
    Particle *temp;


    eDirection direction;
    eDirection lastDirection;

    std::deque<std::pair< eTurn, int>> turns;
    std::vector<Particle *> dSnake;

    int health;

};

#endif //NIBLER_SNAKE_H
