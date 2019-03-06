//
// Created by Vyachealav MARTYNUIK on 2019-01-11.
//
#include "ErrorException.h"
#include "Game.h"

Game::Game() {
    _width = MIN_SIZE;
    _height = MIN_SIZE;
    initGame();
}

Game::Game(char *wStr, char *hStr) {

    checkInputData(wStr, hStr);
    initGame();
}

Game::~Game()
{
    this->dLibManager.destroySoundsPlayer(this->_sPlayer);
    if (_menu)
        delete _menu;
    if (_levelManager)
        delete _levelManager;
    clearGameObjects();
}

void Game::initGame() {


    try{
        this->_render = dLibManager.createRender();
        this->_render->createWindow(_width,  _height);
        this->_sPlayer = dLibManager.createSoundsPlayer();
    }
    catch(...)
    {
        throw (ErrorException("Could not init resources!"));
    }
    if (!(this->_menu = new Menu(_width, _height, running, _render, _sPlayer, &(this->speed), &dLibManager)))
        throw (ErrorException("No space for Menu_object to create"));
    _levelManager = new Level(_width);
    this->_snake.startSnake(this->_width,this->_height);
    if (!(this->generator = new RandomObjGenerator(&this->_obstacles, &this->_apples, this->_width, this->_height)))
        throw (ErrorException("No space for RandObjGenerator_object to create"));
    srand(time(0));
    this->speed = 33;
    this->difficulty = 7;
    this->running = 1;
    this->gameStatus = GAME_STATUS_NBR;
    for (int i = 0; i < difficulty;i++)
        generator->generateObstacle();
    this->generator->generateApple();
}

void Game::checkInputData(char *wStr, char *hStr) {

    std::regex nbrExpression("([1-9])[0-9]+$");
    if (std::regex_match(wStr, nbrExpression) && std::regex_match(hStr, nbrExpression))
    {
        _width = std::stoi(wStr);
        _height = std::stoi(hStr);
        if (_width < MIN_SIZE || _width > MAX_SIZE || _height < MIN_SIZE || _height > MAX_SIZE)
            throw std::invalid_argument("Error! Inappropriate indicating of window's sizes!");
    }
    else
        throw std::invalid_argument("Error! Inappropriate indicating of window's sizes!");
}

void   Game::updateKeyBoardEvent() {

    pressed = _render->keyBoardEvent();
    switch (pressed) {

        case DLIB1:
            this->speed = 33;
            loadRender(SDL);
            break;
        case DLIB2:
            this->speed = 43;
            loadRender(SFML);
            break;
        case DLIB3:
            this->speed = 5;
            loadRender(OPENGL);
            break;
        case EXIT:
          this->running = 0;
            break;
        case MENU:
            this->_render = _menu->runMenu(GAME, this->_render);
            if (!running || _menu->getMenuStatus() == MAIN)
                this->_snake.setHealth(-1);
            break;
        case UP:
            this->_snake.setDir(WEST);
            break;
        case DOWN:
            this->_snake.setDir(EAST);
            break;
        case LEFT:
            this->_snake.setDir(SOUTH);
            break;
        case RIGHT:
            this->_snake.setDir(NORTH);
            break;
       case DEFAULT:
           this->running = 1;
        default:
            return;
    }
}

void    Game::drawGame() {

    drawBoard();
    if (!_apples.empty())
    {
        for (auto &it : _apples) {
            if(it->getType() == APPLE)
                this->_render->drawTexture(APPLE_TEXT, it->getX(), it->getY());
            else if (it->getType() == SUPER_APPLE)
                this->_render->drawTexture(SUPER_APPLE_TEXT, it->getX(), it->getY());
        }
    }
    for(auto& it : _obstacles) {
        if(it->getType() == FRAME)
            this->_render->drawTexture(FRAME_TEXT, it->getX(), it->getY());
        else
            this->_render->drawTexture(OBSTACLE_TEXT, it->getX(), it->getY());
    }
    drawSnake(_snake.getSnake(), _snake.getHealth());
}

void     Game::drawSnake(std::vector<Particle*> snakeParticles, int health) {

    if (health)
    {
        _render->drawRotTexture(SNAKE_HEAD, snakeParticles.front()->getX(), snakeParticles.front()->getY(), snakeParticles.front()->getDirr());
        for(auto it = snakeParticles.begin() + 1; it < snakeParticles.end() - 1; it++){

            if((*it)->getTurn() == ONTHELEFT)
            {
                _render->drawRotTexture(SNAKE_BODY_LEFT, (*it)->getX(), (*it)->getY(), (*it)->getDirr());
            }
            else if((*it)->getTurn() == ONTHERIGHT)
            {
                _render->drawRotTexture(SNAKE_BODY_RIGHT, (*it)->getX(), (*it)->getY(), (*it)->getDirr());
            }
            else
            {
                _render->drawRotTexture(SNAKE_BODY, (*it)->getX(), (*it)->getY(), (*it)->getDirr());
            }
        }
        if(snakeParticles.back()->getTurn() == ONTHELEFT)
            _render->drawRotTexture(SNAKE_TAIL_LEFT, snakeParticles.back()->getX(), snakeParticles.back()->getY(), snakeParticles.back()->getDirr());
        else if(snakeParticles.back()->getTurn() == ONTHERIGHT)
            _render->drawRotTexture(SNAKE_TAIL_RIGHT, snakeParticles.back()->getX(), snakeParticles.back()->getY(), snakeParticles.back()->getDirr());
        else
            _render->drawRotTexture(SNAKE_TAIL, snakeParticles.back()->getX(), snakeParticles.back()->getY(), snakeParticles.back()->getDirr());
    }
    else {
        _render->drawRotTexture(SNAKE_HEAD_DEAD, snakeParticles.front()->getX(), snakeParticles.front()->getY(), snakeParticles.front()->getDirr());
        for(auto it = snakeParticles.begin() + 1; it < snakeParticles.end() - 1; it++){

            if((*it)->getTurn() == ONTHELEFT)
            {
                _render->drawRotTexture(SNAKE_BODY_LEFT_DEAD, (*it)->getX(), (*it)->getY(), (*it)->getDirr());
            }
            else if((*it)->getTurn() == ONTHERIGHT)
            {
                _render->drawRotTexture(SNAKE_BODY_RIGHT_DEAD, (*it)->getX(), (*it)->getY(), (*it)->getDirr());
            }
            else
            {
                _render->drawRotTexture(SNAKE_BODY_DEAD, (*it)->getX(), (*it)->getY(), (*it)->getDirr());
            }
        }
        if(snakeParticles.back()->getTurn() == ONTHELEFT)
            _render->drawRotTexture(SNAKE_TAIL_LEFT_DEAD, snakeParticles.back()->getX(), snakeParticles.back()->getY(), snakeParticles.back()->getDirr());
        else if(snakeParticles.back()->getTurn() == ONTHERIGHT)
            _render->drawRotTexture(SNAKE_TAIL_RIGHT_DEAD, snakeParticles.back()->getX(), snakeParticles.back()->getY(), snakeParticles.back()->getDirr());
        else
            _render->drawRotTexture(SNAKE_TAIL_DEAD, snakeParticles.back()->getX(), snakeParticles.back()->getY(), snakeParticles.back()->getDirr());
    }
}

void    Game::runGameLoop()
{
    int i = 1;
    while (running)
    {
        this->_render = _menu->runMenu(MAIN, this->_render);
        if(!this->running)
            break;
        while (_snake.getHealth()) {
            this->_render->clearWindow();
            refreshSuperApple();
            if (i % (this->speed - (_levelManager->getCurrentLevel())) == 0)
            {
                movingSnakeAndColide();
                updateKeyBoardEvent();
                if ((this->gameStatus = checkGameStatus(_levelManager->update())) == WIN ||
                this->gameStatus == FAIL)
                    break;
            }
            drawGame();
            _levelManager->drawStatistics(this->_render);
            this->_render->updateWindow();
            if (!this->running)
                break;
            if (_menu->getMenuStatus() == MAIN) {
                refreshGame();
                _menu->setMenuStatus(GAME);
            }
            i++;
        }
        if (!_snake.getHealth() || this->gameStatus == FAIL || this->gameStatus == WIN)
            flashSnake();
        refreshGame();
    }
}

void    Game::playFinalSound() {

    this->_sPlayer->stopMusic();
    if (this->gameStatus == FAIL || !_snake.getHealth())
        this->_sPlayer->playSound(FAIL_SOUND);
    else if(this->gameStatus == WIN)
        this->_sPlayer->playSound(WIN_SOUND);
    else if(this->gameStatus == NEXT_LEVEL)
        this->_sPlayer->playSound(MOVE);
}

void    Game::flashSnake() {

    int i = 100;
    int flash_time = 10;
    int posInfoX = this->_width / 2 - 3;
    int posInfoY = this->_width / 2 - 3;
    playFinalSound();
    while (flash_time > 0)
    {
        if (i % (speed * 3) == 0) {
            clock_t time_end = clock() + 1000;
            while (clock() < time_end) {
                this->_render->clearWindow();
                this->_render->updateWindow();
            }
            flash_time--;
        }
        drawGame();
        if (this->gameStatus == FAIL)
            this->_render->renderText("TIME IS OUT!!", posInfoX - 2, posInfoY, WIN_FAIL_FONT, EXTRA);
        else if (this->gameStatus == WIN)
            this->_render->renderText("YOU WON!!!", posInfoX, posInfoY, WIN_FAIL_FONT, HIGHLIGHT);
        else if (!_snake.getHealth())
            this->_render->renderText("FAIL!!!", posInfoX, posInfoY, WIN_FAIL_FONT, EXTRA);
        this->_render->updateWindow();
        i++;
    }
}

void    Game::clearGameObjects()
{
    for (auto &it :_apples)
        if(it)
            delete it;
    _apples.clear();
    for (auto &it :_obstacles)
        if(it)
            delete it;
    _obstacles.clear();
}

eGameStatus    Game::checkGameStatus(eGameStatus status) {

    switch(status) {

        case WIN:
            this->_snake.refreshSnake();
            this->_snake.startSnake(this->_width,this->_height);
            _menu->setMenuStatus(MAIN);
            break;
        case NEXT_LEVEL:
            this->_sPlayer->playSound(MOVE);
            this->_snake.refreshSnake();
            this->generator->refreshObstacles(this->difficulty * _levelManager->getCurrentLevel());
            this->generator->refreshApples();
            this->_snake.startSnake(this->_width,this->_height);
            //hook up next DLIB
            break;
        case FAIL:
            this->_snake.setHealth(0);
            _menu->setMenuStatus(MAIN);
            break;
        default:
            return (status);
    }
    return (status);
}

void        Game::refreshGame() {

    this->_snake.refreshSnake();
    this->_snake.startSnake(this->_width,this->_height);
    this->generator->refreshObstacles(this->difficulty);
    this->generator->refreshApples();
    _levelManager->refreshLevel();
}

void        Game::refreshSuperApple() {

if (((clock() - generator->getClockSA()) / CLOCKS_PER_SEC) == TIME_DESTROY)
    {
       int k = 0;
       for (auto &it : this->_apples)
       {
           if (it->getType() == SUPER_APPLE)
           {
              it->setType(NOTYPE);
              delete it;
              _apples.erase(_apples.begin() + k);
           }
           k++;
       }
    }
}

void    Game::movingSnakeAndColide() {

    eCollideType check;

    this->_snake.move();
    if ((check = this->_snake.collide(&this->_apples, this->_obstacles)) == CAPPLE)
    {
        _sPlayer->playSound(EAT);
        generator->generateApple();
        _levelManager->plusPoint();
    }
    else if (check == CSUPER_APPLE)
    {
        _sPlayer->playSound(SUPER_EAT);
        _levelManager->superApple();
    }
}

void    Game::drawBoard() {

    for(int x = 1; x < _width - 1; x++)
    {
        for(int y = 1; y < _height - 1; y++)
            _render->drawTexture(BOARD, x, y);
    }
}

void    Game::loadRender(eDLib type) {

    this->dLibManager.destroyRender(this->_render);
    this->dLibManager.reload(type);
    try
    {
        this->_render = dLibManager.createRender();
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
        this->dLibManager.destroyRender(this->_render);
        throw (ErrorException("Could not init resources!"));
    }
}
