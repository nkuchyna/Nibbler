//
// Created by Nadiia KUCHYNA on 2019-01-17.
//

#include "Menu.h"

Menu::Menu(int width, int height, bool &running, IRender *render, ISPlayer *sPlayer ,int *speed, DLibManager *dLibManPtr) : _render(render), _sPlayer(sPlayer), dLibManager(dLibManPtr),
                                                                                        _runGame(running), _width(width),_height(height), _speedy(speed)  {
    _centerX = width / 2 + 1;
    _centerY = height / 2 - 1;
    defineFieldsPosition();

    _runMenu = true;
    _menuStatus = MAIN;
    _pressed = DEFAULT;
    _startField = START_NEW_GAME;
    _currentField = START_NEW_GAME;

    _s_map_menuFieldColor[CONTINUE_GAME] = TEXT;
    _s_map_menuFieldColor[START_NEW_GAME] = HIGHLIGHT;
    _s_map_menuFieldColor[RULES_CONTROL] = REGULAR;
    _s_map_menuFieldColor[EXIT_GAME] = TEXT;
}

Menu::~Menu() {
}

void Menu::defineFieldsPosition()
{
    _xPosArr[0] = _centerX - 5;
    _yPosArr[0] = _centerY - 4;
    for (int i = 1; i < FIELDS_NBR; i++)
    {
        _xPosArr[i] = _xPosArr[i - 1];
        _yPosArr[i] = _yPosArr[i - 1] + 2;
    }
}

void Menu::draw()
{
    _render->clearWindow();
    drawBorder();
    drawBoard();
    if (_menuStatus == MAIN)
    {
        _render->renderText("START GAME", _xPosArr[START_NEW_GAME], _yPosArr[START_NEW_GAME], MENU_FONT, _s_map_menuFieldColor[START_NEW_GAME]);
        _render->renderText("RULES", _xPosArr[RULES_CONTROL], _yPosArr[RULES_CONTROL], MENU_FONT, _s_map_menuFieldColor[RULES_CONTROL]);
        _render->renderText("EXIT GAME", _xPosArr[EXIT_GAME], _yPosArr[EXIT_GAME], MENU_FONT, _s_map_menuFieldColor[EXIT_GAME]);
    }
    else if (_menuStatus == GAME)
    {
        _render->renderText("CONTINUE GAME", _xPosArr[CONTINUE_GAME], _yPosArr[CONTINUE_GAME], MENU_FONT, _s_map_menuFieldColor[CONTINUE_GAME]);
        _render->renderText("START NEW GAME", _xPosArr[START_NEW_GAME], _yPosArr[START_NEW_GAME], MENU_FONT, _s_map_menuFieldColor[START_NEW_GAME]);
        _render->renderText("RULES", _xPosArr[RULES_CONTROL], _yPosArr[RULES_CONTROL], MENU_FONT, _s_map_menuFieldColor[RULES_CONTROL]);
        _render->renderText("EXIT GAME", _xPosArr[EXIT_GAME], _yPosArr[EXIT_GAME], MENU_FONT, _s_map_menuFieldColor[EXIT_GAME]);
    }

    _render->updateWindow();
}

void    Menu::drawInfo() {

    while(1)
    {
        _pressed = _render->keyBoardEvent();
        if (_pressed == ENTER || _pressed == MENU)
            break;
        else if(_pressed == EXIT)
        {
            _runMenu = 0;
            _runGame = 0;
            break;
        }
        _render->clearWindow();
        _render->renderText("---------------- RULES ----------------", _xPosArr[START_NEW_GAME] - 4, _yPosArr[START_NEW_GAME], MENU_FONT, REGULAR);
        _render->renderText("- Use ARROWS to control movements of the SNAKE", _xPosArr[START_NEW_GAME] - 4, _yPosArr[START_NEW_GAME] + 2, INFO_FONT, REGULAR);
        _render->renderText("- The SNAKE can not move backwards!", _xPosArr[START_NEW_GAME] - 4, _yPosArr[START_NEW_GAME] + 4, INFO_FONT, REGULAR);
        _render->renderText("- The GOAL: to feed your SNAKE!", _xPosArr[START_NEW_GAME] - 4, _yPosArr[START_NEW_GAME] + 6, INFO_FONT, REGULAR);
        _render->renderText("...........Press ENTER to continue", _xPosArr[START_NEW_GAME] - 4, _yPosArr[START_NEW_GAME] + 8, INFO_FONT, REGULAR);
        _render->updateWindow();
    }
}

void    Menu::updateKeyBoardEvent() {

    _pressed = _render->keyBoardEvent();
    switch (_pressed) {
        case DLIB1:
            *(this->_speedy) = 33;
            loadRender(SDL);
            break;
        case DLIB2:
            *(this->_speedy) = 43;
            loadRender(SFML);
            break;
        case DLIB3:
            *(this->_speedy) = 5;
            loadRender(OPENGL);
            break;
        case EAST :
            if (_currentField != _startField)
            {
                _currentField -= 1;
                _s_map_menuFieldColor[eMenuFields(_currentField)] = HIGHLIGHT;
                _s_map_menuFieldColor[eMenuFields(_currentField + 1)] = TEXT;
            }
            break;
        case WEST :
            if (_currentField < (int)FIELDS_NBR - 1)
            {
                _currentField += 1;
                _s_map_menuFieldColor[eMenuFields(_currentField)] = HIGHLIGHT;
                _s_map_menuFieldColor[eMenuFields(_currentField - 1)] = TEXT;
            }
            break;
        case EXIT :
            _runMenu = false;
            _runGame = false;
            break;
        case ENTER:
            if (eMenuFields(_currentField) == CONTINUE_GAME) {
                _runMenu = false;
            }
            else if (eMenuFields(_currentField) == START_NEW_GAME) {
                _runMenu = false;
                if (_menuStatus == MAIN)
                    _menuStatus = GAME;
                else if (_menuStatus == GAME)
                    _menuStatus = MAIN;
            }
            else if (eMenuFields(_currentField) == EXIT_GAME)
            {
                _runMenu = false;
                _runGame = false;
            }
            else if (eMenuFields(_currentField) == RULES_CONTROL)
                drawInfo();
            return;
        default:
            return;
    }
    this->_sPlayer->playSound(CLICK);
}

void    Menu::refreshMenu(eMenuStatus status)
{
    _menuStatus = status;
    _pressed = DEFAULT;
    _s_map_menuFieldColor[CONTINUE_GAME] = HIGHLIGHT;
    _s_map_menuFieldColor[RULES_CONTROL] = TEXT;
    _s_map_menuFieldColor[EXIT_GAME] = TEXT;
    if (status == MAIN)
    {
        _startField = START_NEW_GAME;
        _currentField = START_NEW_GAME;
        _s_map_menuFieldColor[START_NEW_GAME] = HIGHLIGHT;
    }
    else if (status == GAME)
    {
        _startField = CONTINUE_GAME;
        _currentField = CONTINUE_GAME;
        _s_map_menuFieldColor[START_NEW_GAME] = TEXT;
    }
}

IRender*    Menu::runMenu(eMenuStatus status, IRender *rend) {

    this->_render = rend;
    _runMenu = true;
    refreshMenu(status);
    this->_sPlayer->playMusic(MENU_MUSIC);
    while (_runMenu){
        _render->clearWindow();
        draw();
        updateKeyBoardEvent();
    }
    this->_sPlayer->playMusic(GAME_MUSIC);
    return this->_render;
}

eMenuStatus Menu::getMenuStatus() const {

    return (this->_menuStatus);
}

void    Menu::setMenuStatus(const eMenuStatus status) {

    this->_menuStatus = status;
}

void    Menu::drawBorder() {

    for(int x = 0; x < _width; x++)
    {
        _render->drawTexture(FRAME_TEXT, x, 0);
        _render->drawTexture(FRAME_TEXT, x, _height - 1);
    }
    for(int y = 1; y < _height - 1; y++)
    {
        _render->drawTexture(FRAME_TEXT, 0, y);
        _render->drawTexture(FRAME_TEXT, _width - 1, y);
    }
}

void    Menu::drawBoard() {

    for(int x = 1; x < _width - 1; x++)
    {
        for(int y = 1; y < _height - 1; y++)
            _render->drawTexture(MAIN_BOARD, x, y);
    }
}

void    Menu::loadRender(eDLib type) {


    this->dLibManager->destroyRender(this->_render);

    this->dLibManager->reload(type);
    try
    {
        this->_render = dLibManager->createRender();
    }
    catch(...){

        throw (ErrorException("invalid DLIB initialization!"));
    }
    try
    {
        this->_render->createWindow(this->_width, this->_height);
    }
    catch(ErrorException &ex)
    {
        this->dLibManager->destroyRender(this->_render);
        throw (ErrorException("Could not init resources!"));
    }
}
