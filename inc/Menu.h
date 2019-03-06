//
// Created by Nadiia KUCHYNA on 2019-01-17.
//

#ifndef NIBLER_MENU_H
#define NIBLER_MENU_H
#include "Nibbler.h"
#include "IRender.h"
//#include "ISPlayer.h"
#include "DLibManager.h"
#include <iostream>

enum eMenuFields {
    CONTINUE_GAME,
    START_NEW_GAME,
    RULES_CONTROL,
    EXIT_GAME,
    FIELDS_NBR
};

class Menu {

public:
    Menu() = delete;
    Menu(int width, int height, bool &running, IRender *render, ISPlayer *sPlayer ,int *speed, DLibManager *dLibManPtr);
    Menu(const Menu &obj) = delete;
    Menu&   operator=(const Menu &obj) = delete;
    ~Menu();

    eMenuStatus getMenuStatus() const;
    void        setMenuStatus(const eMenuStatus status);
    IRender*    runMenu(eMenuStatus status, IRender *rend);

private:


    IRender         *_render;
    ISPlayer        *_sPlayer;
    DLibManager     *dLibManager;
    bool            &_runGame;
    bool            _runMenu;
    eMenuStatus     _menuStatus;
    eKeys           _pressed;
    int             _currentField;
    int             _startField;
    int             _centerX;
    int             _centerY;
    int             _width;
    int             _height;
    int             _xPosArr[FIELDS_NBR];
    int             _yPosArr[FIELDS_NBR];

    int *           _speedy;
    std::map<eMenuFields, eColors>    _s_map_menuFieldColor;

    void    defineFieldsPosition();
    void    refreshMenu(eMenuStatus status);
    void    updateKeyBoardEvent();
    void    draw();
    void    drawInfo();
    void    drawBorder();
    void    drawBoard();
    void    loadRender(eDLib type);
};

#endif //NIBLER_MENU_H
