//
// Created by Nadiia KUCHYNA on 2019-01-19.
//

#ifndef NIBLER_LEVEL_H
#define NIBLER_LEVEL_H
#include "IRender.h"
#include "Nibbler.h"

enum eStatisticFields {

    CURRENT_LEVEL,
    TIME,
    POINTS,
    STATISTIC_FIELDS_NBR
};

class Level {

public:
    Level();
    Level(int width);
    ~Level();
    Level(const Level &obj);
    Level&  operator=(const Level &obj);

    int             getCurrentLevel() const;
    eGameStatus     update();
    void            plusPoint();
    void            drawStatistics(IRender *);
    void            refreshLevel();
    void            superApple();

private:
    eGameStatus     _gameStatus;

    int     _currentLevel;
    int     _points;
    int     _time;

    int     _statistic[STATISTIC_FIELDS_NBR];
    int     _winPoints[LEVELS_NBR];
    int     _posX[STATISTIC_FIELDS_NBR];
    int     _posY[STATISTIC_FIELDS_NBR];

    void    nextLevelUp();
    void    centerLevel(int width);
};

#endif //NIBLER_LEVEL_H
