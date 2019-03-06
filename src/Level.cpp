//
// Created by Nadiia KUCHYNA on 2019-01-19.
//

#include "Level.h"

Level::Level() {

    _winPoints[FIRST] = 2;
    _winPoints[SECOND] = 2;
    _winPoints[THIRD] = 2;
    _currentLevel = 0;
    refreshLevel();
    centerLevel(MIN_SIZE);
}

Level::Level(int width) {

    //Init win points nbr levels' conditions
    _winPoints[FIRST] = 5;
    _winPoints[SECOND] = 10;
    _winPoints[THIRD] = 15;
    _currentLevel = 0;
    refreshLevel();
    centerLevel(width);
}

Level::~Level() {}

Level::Level(const Level &obj) {
    *this = obj;
}

Level&  Level::operator=(const Level &obj) {

    if(&obj != this)
    {
        this->_currentLevel = obj._currentLevel;
        this->_points = obj._points;
        this->_time = obj._time;
        for(int i = 0; i < STATISTIC_FIELDS_NBR; i++)
            this->_statistic[i] = obj._statistic[i];
        for(int i = 0; i < LEVELS_NBR; i++)
            this->_winPoints[i] = obj._winPoints[i];
        for(int i = 0; i < STATISTIC_FIELDS_NBR; i++)
            this->_posX[i] = obj._posX[i];
        for(int i = 0; i < STATISTIC_FIELDS_NBR; i++)
            this->_posY[i] = obj._posY[i];
    }
    return (*this);
}

int     Level::getCurrentLevel() const {

    return (this->_statistic[CURRENT_LEVEL]);
}

void    Level::drawStatistics(IRender * render) {

    render->renderText("Level: " + std::to_string(_statistic[CURRENT_LEVEL] + 1), _posX[CURRENT_LEVEL], _posY[CURRENT_LEVEL], GAME_FONT, REGULAR);
    render->renderText("Points: " + std::to_string(_statistic[POINTS]) + "/" + std::to_string(_winPoints[_statistic[CURRENT_LEVEL]]), _posX[POINTS], _posY[POINTS], GAME_FONT, REGULAR);
    render->renderText("Time: " + std::to_string(_statistic[TIME]), _posX[TIME], _posY[TIME], GAME_FONT, REGULAR);
}

void    Level::nextLevelUp() {

    _statistic[CURRENT_LEVEL] = _statistic[CURRENT_LEVEL] + 1;
    _statistic[POINTS] = 0;
    _statistic[TIME] = 300;
}

void    Level::refreshLevel() {

    _statistic[CURRENT_LEVEL] = 0;
    _statistic[POINTS] = 0;
    _statistic[TIME] = 300;
}

void    Level::centerLevel(int width) {

    int     step = width / STATISTIC_FIELDS_NBR;
    int     x = 0;
    for(int i = CURRENT_LEVEL; i < STATISTIC_FIELDS_NBR; i++)
    {

        _posX[i] = x + 2;
        _posY[i] = 1;
        x += step;
    }
}

eGameStatus    Level::update() {

    _gameStatus = GAME_STATUS_NBR;

    if(_statistic[POINTS] >= _winPoints[_statistic[CURRENT_LEVEL]])
    {
        this->nextLevelUp();
        if(_statistic[CURRENT_LEVEL] == LEVELS_NBR)
            _gameStatus = WIN;
        else
        {
            _statistic[TIME] = 300 * ((this->_statistic[CURRENT_LEVEL]) + 1 * (this->_statistic[CURRENT_LEVEL] + 1));
            _gameStatus = NEXT_LEVEL;
        }
    }
    else if(!(_statistic[TIME] -= 1)) {
        _gameStatus = FAIL;
        refreshLevel();

    }
    return (_gameStatus);
}

void    Level::plusPoint() {

    _statistic[POINTS] += 1;
}

void Level::superApple()
{
    _statistic[TIME] += 90;
    _statistic[POINTS] += 3;
}
