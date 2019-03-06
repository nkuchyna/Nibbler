//
// Created by Vyachealav MARTYNUIK on 2019-01-11.
//

#include "Particle.h"
Particle::Particle() {}

Particle::Particle(int x, int y, eParticle type) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->dirr = NORTH;
    this->turn = NONE;
}
Particle::Particle(Particle const &src) {
    *this = src;
    return;
}

Particle const& Particle::operator=(Particle const &src) {
    this->x = src.getX();
    this->y = src.getY();
    this->type = src.getType();
    this->dirr = src.getDirr();
    return src;
}

Particle::~Particle() {}

eTurn Particle::getTurn() const
{
    return this->turn;
}
void Particle::setTurn(eTurn t)
{
    this->turn = t;
}

int Particle::getX() const {
    return this->x;
}

int Particle::getY() const{
    return this->y;
}
void Particle::setX(int x) {
    this->x = x;
}
void Particle::setY(int y) {
    this->y = y;
}

eParticle Particle::getType() const {
    return this->type;
}

void Particle::setType(eParticle sym) {
    Particle::type = sym;
}

void Particle::setDirr(eDirection d)
{
    this->dirr = d ;
}
eDirection Particle::getDirr() const
{
    return this->dirr;
}

bool Particle::equals(Particle &src)
{
    if (this->x == src.getX() && this->y == src.getY())
        return true;
    else
        return false;
}
