//
// Created by Vyachealav MARTYNUIK on 2019-01-11.
//

#ifndef NIBBLER_NIBBLER_H
#define NIBBLER_NIBBLER_H
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <dlfcn.h>

#define MIN_SIZE 30
#define MAX_SIZE 40

enum eMenuStatus
{
    MAIN = 0,
    GAME,
    INFO
};

enum  eDirection
{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    DIRECTION_NBR
};

enum eDLib
{
    SDL,
    SFML,
    OPENGL,
    SDL_MIXER
};

enum eParticle
{
    SNAKE,
    OBSTACLE,
    FRAME,
    APPLE,
    SUPER_APPLE,
    NOTYPE
};

enum eTurn
{
    ONTHELEFT,
    ONTHERIGHT,
    NONE
};

enum eGameStatus
{

    NEXT_LEVEL,
    WIN,
    FAIL,
    GAME_STATUS_NBR
};

enum eCollideType
{
    COBSTACLE,
    CAPPLE,
    CSUPER_APPLE,
    NOTHING
};

enum eLevels
{
    FIRST,
    SECOND,
    THIRD,
    LEVELS_NBR
};

#endif
