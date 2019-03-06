//
// Created by Vyachealav MARTYNUIK on 2019-01-11.
//

#ifndef NIBBLER_GAME_H
#define NIBBLER_GAME_H

#include <iostream>
#include <regex>
#include "Snake.h"
#include "DLibManager.h"
#include "RandomObjGenerator.h"
#include <ctime>
#include "Menu.h"
#include "Level.h"

#define TIME_DESTROY 2

class Game {

    int _width;
    int _height;
    static int count_ofObstacles;

public:
    Game();
    Game (char *wStr, char *hStr);
    Game(Game const &) = delete;
    Game &operator=(Game const &obj) = delete;
    ~Game();

    //////getters
    int     getWidth() const;
    int     getHeight() const;
    /////////////
    void    runGameLoop();
    void    startGame();
    void    createObsticles();

private:
    int                 speed;
    int                 difficulty;
    DLibManager         dLibManager;
    Snake               _snake;
    RandomObjGenerator *generator;

    std::vector<Particle *> _obstacles;
    std::vector<Particle *> _apples;

    IRender     *_render;
    ISPlayer    *_sPlayer;
    Menu        *_menu;
    Level       *_levelManager;
    eGameStatus gameStatus;
    bool        running;
    eKeys       pressed;

    void        checkInputData(char *wStr, char *hStr);
    void        initGame();

    void        updateKeyBoardEvent();
    void        drawGame();
    void        drawSnake(std::vector<Particle*> snakeParticles, int health);
    void        flashSnake();
    void        clearGameObjects();
    eGameStatus checkGameStatus(eGameStatus status);

    void    generateApples();
    void    generateObstacles();
    void    generateRandPosition(int *x, int *y);

    void    playFinalSound();
    void    refreshGame();
    void    refreshSuperApple();
    void    movingSnakeAndColide();
    void    drawBoard();
    void    loadRender(eDLib type);
};

#endif //NIBLER_GAME_H
