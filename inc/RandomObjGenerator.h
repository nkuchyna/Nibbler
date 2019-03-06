//
// Created by Nadiia KUCHYNA on 2019-01-19.
//

#ifndef NIBLER_RANDOMOBJGENERATOR_H
#define NIBLER_RANDOMOBJGENERATOR_H

#include "Nibbler.h"
#include "Particle.h"
#include "Level.h"

class   RandomObjGenerator {

public:
    RandomObjGenerator();
    RandomObjGenerator( std::vector<Particle *> *_obstacles, std::vector<Particle *> *_apples, int w, int h);
    ~RandomObjGenerator();
    RandomObjGenerator(const RandomObjGenerator &obj);
    RandomObjGenerator& operator=(const RandomObjGenerator &obj);

    //getters
    clock_t getClockSA();
    std::vector<Particle *> * getObstacles() const;
    std::vector<Particle *> * getApples() const;
    void setObstacles( std::vector<Particle *> *);
    void setApples(std::vector<Particle *> *);
    void setClockSA(clock_t);

    void generateObstacle();
    void generateApple();
    bool checkObstacles(int x, int y);
    void refreshObstacles(int);
    void refreshApples();

private:
    std::vector<Particle *> *_obstacles;
    std::vector<Particle *> *_apples;

    clock_t clockSuperApple;
    int _width;
    int _height;
    int countOfObstacles;


    void        generateRandPosition(int *x, int *y);
};

static int superA = 1;
#endif //NIBLER_RANDOMOBJGENERATOR_H
