//
// Created by Vyachealav MARTYNUIK on 2019-01-11.
//
#include "ErrorException.h"
#include "Snake.h"

Snake::Snake() {
    health = 1;
    try {
        this->dSnake.push_back(new Particle(0, 0, SNAKE));
        this->dSnake.push_back(new Particle(0, 1, SNAKE));
        this->dSnake.push_back(new Particle(0, 2, SNAKE));
        this->dSnake.push_back(new Particle(0, 3, SNAKE));
        this->dSnake.push_back(new Particle(0, 4, SNAKE));
    }
    catch (std::bad_alloc& ba)
    {
        throw new ErrorException("The memory was not allocated for snake");
    }
    this->direction = WEST;
    this->lastDirection = DIRECTION_NBR;
    turns.clear();
    temp = new Particle();
}

Snake::Snake(Snake const &src) {
    *this = src;
    return;
}

Snake const& Snake::operator=(Snake const &src) {
    return src;
}
Snake::~Snake() {
    for (auto &it :dSnake)
    {
        delete it;
    }
}

bool Snake::oppositeDir(eDirection now, eDirection next)
{
    if (now == EAST && next == WEST)
        return true;
    else if (now == WEST && next == EAST)
        return true;
    else if (now == NORTH && next == SOUTH)
        return true;
    else if (now == SOUTH && next == NORTH)
        return true;
    else
        return false;

}

eDirection Snake::getDir() {
    return this->direction;
}
void Snake::setDir(eDirection dir) {
    if (!this->oppositeDir(this->getDir(), dir)) {
        this->lastDirection = this->direction;
        this->direction = dir;
    }
}

std::vector <Particle *> &Snake::getSnake() {
    return this->dSnake;
}

int Snake::getHealth() {
    return this->health;
}
void Snake::setHealth(int x)
{
    this->health = x;
}

void Snake::startSnake(int w, int h)
{
    this->_mapWidth = w;
    this->_mapHeight = h;
    int x = w / 2;
    int y = h / 2;
    for (auto &it: this->dSnake)
    {
        it->setX(it->getX() + x);
        it->setY(it->getY() + y);
    }
}

eTurn Snake::whereTo() {
    if (this->getDir() == lastDirection) {
        return NONE;
    }
    if (!this->oppositeDir(this->getDir(), lastDirection)) {
        if (this->direction == NORTH && lastDirection == WEST) {
            lastDirection = this->getDir();
            return ONTHERIGHT;
        } else if (this->direction == EAST && lastDirection == NORTH) {
            lastDirection = this->getDir();
            return ONTHERIGHT;
        } else if (this->direction == SOUTH && lastDirection == EAST) {
            lastDirection = this->getDir();
            return ONTHERIGHT;
        } else if (this->direction == WEST && lastDirection == SOUTH) {
            lastDirection = this->getDir();
            return ONTHERIGHT;
        } else if (this->direction == EAST && lastDirection == SOUTH) {
            lastDirection = this->getDir();
            return ONTHELEFT;
        } else if (this->direction == SOUTH && lastDirection == WEST) {
            lastDirection = this->getDir();
            return ONTHELEFT;
        } else if (this->direction == WEST && lastDirection == NORTH) {
            lastDirection = this->getDir();
            return ONTHELEFT;
        } else if (this->direction == NORTH && lastDirection == EAST) {
            lastDirection = this->getDir();
            return ONTHELEFT;
        } else {
            return NONE;
        }
    } else {
        lastDirection = this->getDir();
        return NONE;
    }
}

void Snake::move()
{
////места поворотов в векторе змея
    if (!turns.empty()) {
           for (int i = 0; i < (int)turns.size(); i++) {
            if (turns[i].second <= (int)dSnake.size()) {
                turns[i].second++;
            }
            else
            {
                turns.erase(turns.begin() + i);
            }

        }

    }
    int k = 0;
    eTurn povorot;
    ////перемещение змейки за один мув////
       for( int i = 0; i < (int)dSnake.size(); i++) {
       ////фиксация положения головы в темп и смещение ее согласно клавише
       if (i == 0)
        {
            *temp = *dSnake[i];
            if (this->direction == NORTH) {
                if ((povorot = whereTo()) != NONE)
                    turns.push_front(std::make_pair(povorot, 1));
                dSnake[i]->setX(dSnake[i]->getX() + 1);
                dSnake[i]->setDirr(EAST);


            }
            else if (this->direction == EAST) {

                if ((povorot = whereTo()) != NONE)
                    turns.push_front(std::make_pair(povorot, 1));
                dSnake[i]->setY(dSnake[i]->getY() + 1);
                dSnake[i]->setDirr(SOUTH);

            }
            else if (this->direction == SOUTH) {

                if ((povorot = whereTo()) != NONE)
                    turns.push_front(std::make_pair(povorot, 1));
                dSnake[i]->setX(dSnake[i]->getX() - 1);
                dSnake[i]->setDirr(WEST);

            }
            else if (this->direction == WEST) {

                if ((povorot = whereTo()) != NONE)
                    turns.push_front(std::make_pair(povorot, 1));
                dSnake[i]->setY(dSnake[i]->getY() - 1);
                dSnake[i]->setDirr(NORTH);

            }
            else
                break;
            temp->setTurn(povorot);
        }
       ///////////////смещение остальных координат за головой за один мув
        else
        {
            eTurn t;
            t = temp->getTurn();
            if (i + 1 < (int)dSnake.size()) {

                Particle temp2;
                temp2 = *dSnake[i];
                *dSnake[i] = *temp;
                *temp = temp2;

              }
            else
                *dSnake[i] = *temp;
        }
//////проверка выхода змеи за предалы поля
         if (dSnake[i]->getX() >= this->_mapWidth)
             dSnake[i]->setX(0);
         if (dSnake[i]->getX() < 0)
             dSnake[i]->setX(this->_mapWidth);
         if (dSnake[i]->getY() >= this->_mapHeight)
             dSnake[i]->setY(0);
         if (dSnake[i]->getY() < 0)
             dSnake[i]->setY(this->_mapHeight);
         k++;
    }
       ///Установка поворотного елемента змейки (или вправо(1) или влево(0))

    for (auto &it :dSnake)
    {
        it->setTurn(NONE);
    }
    if (!turns.empty()) {
        for (int j = 0; j < (int) turns.size(); j++) {
            if (turns[j].second >= 1 && turns[j].second < (int)dSnake.size()) {
                dSnake[turns[j].second]->setTurn(turns[j].first);
            }
            else
                ;
        }
    }
}

eCollideType Snake::collide(std::vector<Particle *> *apples, std::vector<Particle *> obsticles) {

    eCollideType ret =  NOTHING;
    int i = 0;
   while (i < (int)obsticles.size() && this->health == 1)
    {
        if (this->dSnake[0]->equals(*obsticles[i])){
            this->health = 0;
        }
        i++;
    }

    i = 1;
    while (i < (int)dSnake.size() && this->health == 1)
    {
        if (this->dSnake[0]->equals(*this->dSnake[i])) {
            this->health = 0;
        }
            i++;
    }

    i = 0;

    while (i < (int)apples->size() && this->health == 1)
    {

        if (this->dSnake[0]->equals(*(*apples)[i]))
        {
            Particle *app;
            try {
               app = new Particle();
            }
            catch (std::bad_alloc& ba)
            {
                throw new ErrorException("The memory was not allocated for apples");
            }

            *app = *(*apples)[i];
            delete (*apples)[i];
            if (app->getType()== APPLE)
                ret = CAPPLE;
            else if (app->getType() == SUPER_APPLE)
                ret = CSUPER_APPLE;
            app->setType(SNAKE);
            app->setX(dSnake[dSnake.size() - 1]->getX());
            app->setY(dSnake[dSnake.size() - 1]->getY());
            app->setTurn(dSnake[dSnake.size() - 1]->getTurn());
            app->setDirr(dSnake[dSnake.size() - 1]->getDirr());
            this->dSnake.push_back(app);
            apples->erase(apples->begin() + i);
            return ret;
        }
        i++;
    }
    return  ret;

}

void    Snake::refreshSnake(){
    health = 1;

         for (auto &it :dSnake) {
            delete it;
        }
        this->dSnake.clear();
    try {
        this->dSnake.push_back(new Particle(0, 0, SNAKE));
        this->dSnake.push_back(new Particle(0, 1, SNAKE));
        this->dSnake.push_back(new Particle(0, 2, SNAKE));
        this->dSnake.push_back(new Particle(0, 3, SNAKE));
        this->dSnake.push_back(new Particle(0, 4, SNAKE));
    }
    catch (std::bad_alloc& ba)
    {
        throw new ErrorException("The memory was not allocated for snake");
    }
        this->direction = WEST;
        this->lastDirection = DIRECTION_NBR;
        turns.clear();
}

