//
// Created by Vyachealav MARTYNUIK on 2019-01-11.
//

#ifndef NIBBLER_PARTICLE_H
#define NIBBLER_PARTICLE_H
#include "Nibbler.h"

class Particle {

public:
    Particle();
    Particle(Particle const &);
    Particle const &operator=(Particle const &);
    ~Particle();

    Particle(int , int, eParticle );

    int getX() const;
    void setX(int);
    int getY() const ;
    void setY(int);
    eParticle getType() const;
    void setType(eParticle);
    void setDirr(eDirection);
    eDirection getDirr() const;
    eTurn getTurn() const;
    void setTurn(eTurn);

    bool equals(Particle &);

private:
    int x;
    int y;
    eDirection dirr;
    eTurn turn;
    eParticle type;
};

#endif //NIBLER_PARTICLE_H
