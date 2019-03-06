//
// Created by Nadiia KUCHYNA on 2019-01-15.
//

#ifndef NIBLER_IRENDER_H
#define NIBLER_IRENDER_H
#define MENU_WIDTH  300
#define MENU_HEIGHT 50
#include "Nibbler.h"
#include "ErrorException.h"

enum    eKeys
{
    DEFAULT = 0,
    UP,
    RIGHT,
    DOWN,
    LEFT,
    EXIT,
    MENU,
    DLIB1,
    DLIB2,
    DLIB3,
    ENTER
};

enum    eTextures
{
    SNAKE_HEAD = 0,
    SNAKE_BODY,
    SNAKE_BODY_LEFT,
    SNAKE_BODY_RIGHT,
    SNAKE_TAIL,
    SNAKE_TAIL_LEFT,
    SNAKE_TAIL_RIGHT,
    SNAKE_HEAD_DEAD,
    SNAKE_BODY_DEAD,
    SNAKE_BODY_LEFT_DEAD,
    SNAKE_BODY_RIGHT_DEAD,
    SNAKE_TAIL_DEAD,
    SNAKE_TAIL_LEFT_DEAD,
    SNAKE_TAIL_RIGHT_DEAD,
    APPLE_TEXT,
    SUPER_APPLE_TEXT,
    OBSTACLE_TEXT,
    FRAME_TEXT,
    BOARD,
    MAIN_BOARD,
    TEXTURE_NBR
};

enum    eFonts
{
    MENU_FONT = 0,
    GAME_FONT,
    INFO_FONT,
    WIN_FAIL_FONT,
    FONTS_NBR
};

enum    eColors
{
    REGULAR = 0,
    HIGHLIGHT,
    TEXT,
    EXTRA,
    COLORS_NBR
};

class IRender {

public:
    virtual void    createWindow(int width, int heights) = 0;
    virtual eKeys   keyBoardEvent() = 0;
    virtual void    drawTexture(eTextures type, int x, int y) = 0;
    virtual void    drawRotTexture(eTextures type, int x, int y, eDirection direction) = 0;
    virtual void    clearWindow() = 0;
    virtual void    updateWindow() = 0;
    virtual void    renderText(std::string text, int x, int y, eFonts font, eColors color) = 0;
    virtual ~IRender(){}
};

#endif //NIBLER_IRENDER_H
