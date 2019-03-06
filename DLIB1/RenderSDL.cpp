//
// Created by Vyachealav MARTYNUIK on 2019-01-14.
//

#include "RenderSDL.h"
#include <iostream>
#include <time.h>

RenderSDL::RenderSDL() {
    this->init_();
   while (SDL_PollEvent(&this->_event))
       ;
}

RenderSDL::RenderSDL(RenderSDL const &src) {
    *this = src;
}

RenderSDL & RenderSDL::operator=(RenderSDL const &src) {
    if(&src != this)
    {
        SDL_DestroyWindow(this->_window);
        this->_window = src._window;
        this->_event = src._event;
        SDL_DestroyRenderer(this->_renderer);
        this->_renderer = src._renderer;
        for(int i = 0; i < TEXTURE_NBR ; i++)
        {
            if(this->_textArr[i])
                SDL_DestroyTexture(this->_textArr[i]);
            if(src._textArr[i])
                this->_textArr[i] = src._textArr[i];
        }
        for(int i = 0; i < FONTS_NBR ; i++)
        {
            if(this->_fontArr[i])
                TTF_CloseFont(this->_fontArr[i]);
            if(src._fontArr[i])
                this->_fontArr[i] = src._fontArr[i];
        }
        this->_s_map_texturePath.clear();
        this->_s_map_texturePath.insert(src._s_map_texturePath.begin(), src._s_map_texturePath.end());
        this->_s_map_directionDegree.clear();
        this->_s_map_directionDegree.insert(src._s_map_directionDegree.begin(), src._s_map_directionDegree.end());
    }
    return (*this);
}

RenderSDL::~RenderSDL() {
    for(int i = 0; i < TEXTURE_NBR ; i++)
    {
        if(this->_textArr[i])
            SDL_DestroyTexture(this->_textArr[i]);
    }
    for(int i = MENU_FONT; i < FONTS_NBR; i++)
    {
        if(this->_fontArr[i])
            TTF_CloseFont(this->_fontArr[i]);
    }
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_window);
    TTF_Quit();
    IMG_Quit();
//    SDL_Quit();
}

void RenderSDL::init_() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0)
        throw (ErrorException("Error in initialization of SDL"));
    //*************Init textures_paths
    this->_s_map_texturePath[SNAKE_HEAD] = "./DLIB1/resources/snake_head.png";
    this->_s_map_texturePath[SNAKE_BODY] = "./DLIB1/resources/snake_body.png";
    this->_s_map_texturePath[SNAKE_BODY_LEFT] = "./DLIB1/resources/snake_body_left.png";
    this->_s_map_texturePath[SNAKE_BODY_RIGHT] = "./DLIB1/resources/snake_body_right.png";
    this->_s_map_texturePath[SNAKE_TAIL] = "./DLIB1/resources/snake_tail.png";
    this->_s_map_texturePath[SNAKE_TAIL_LEFT] = "./DLIB1/resources/snake_tail_left.png";
    this->_s_map_texturePath[SNAKE_TAIL_RIGHT] = "./DLIB1/resources/snake_tail_right.png";
    this->_s_map_texturePath[SNAKE_HEAD_DEAD] = "./DLIB1/resources/snake_head_death.png";
    this->_s_map_texturePath[SNAKE_BODY_DEAD] = "./DLIB1/resources/snake_body_death.png";
    this->_s_map_texturePath[SNAKE_BODY_LEFT_DEAD] = "./DLIB1/resources/snake_body_left_death.png";
    this->_s_map_texturePath[SNAKE_BODY_RIGHT_DEAD] = "./DLIB1/resources/snake_body_right_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_DEAD] = "./DLIB1/resources/snake_tail_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_LEFT_DEAD] = "./DLIB1/resources/snake_tail_left_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_RIGHT_DEAD] = "./DLIB1/resources/snake_tail_right_death.png";
    this->_s_map_texturePath[APPLE_TEXT] = "./DLIB1/resources/apple.png";
    this->_s_map_texturePath[OBSTACLE_TEXT] = "./DLIB1/resources/obstacle.png";
    this->_s_map_texturePath[FRAME_TEXT] = "./DLIB1/resources/frame1.png";
    this->_s_map_texturePath[BOARD] = "./DLIB1/resources/game_board.png";
    this->_s_map_texturePath[MAIN_BOARD] = "./DLIB1/resources/board.png";
    this->_s_map_texturePath[SUPER_APPLE_TEXT] = "./DLIB1/resources/supper_apple.png";

    //*************Init direction rotation angle
    this->_s_map_directionDegree[NORTH] = 0;
    this->_s_map_directionDegree[EAST] = 90;
    this->_s_map_directionDegree[SOUTH] = 180;
    this->_s_map_directionDegree[WEST] = 270;

    this->_colorsArr[REGULAR] = {188, 174, 118, 255};
    this->_colorsArr[HIGHLIGHT] = {138, 70, 7, 255};
    this->_colorsArr[TEXT] = {72, 64, 39, 255};
    this->_colorsArr[EXTRA] = {100, 20, 0, 255};
}

void    RenderSDL::createWindow(int width, int height) {

    if (!(this->_window = SDL_CreateWindow("Nibbler from SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * SPRITE_SIZE, height * SPRITE_SIZE, SDL_WINDOW_SHOWN)))
        throw (ErrorException("Error in creating SDL window"));

    //*************Create Render and load textures
    if (!(this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED)))
        throw (ErrorException("Error in creating SDL renderer"));
    SDL_SetRenderDrawColor(this->_renderer, 0x60, 0x5A, 0x3C, 0xFF);
    int inittedFlags = IMG_Init(RenderSDL::imgFlags);
    if ((inittedFlags& RenderSDL::imgFlags) != RenderSDL::imgFlags)
        throw (ErrorException("Error in SDL: failed to init required jpg and png support"));
    //*************Init fonts
    this->_fontArr[MENU_FONT] = TTF_OpenFont("./DLIB1/resources/pricedown.black.ttf", 45);
    this->_fontArr[GAME_FONT] = TTF_OpenFont("./DLIB1/resources/alba.super.ttf", 32);
    this->_fontArr[INFO_FONT] = TTF_OpenFont("./DLIB1/resources/OpenSans.ttf", 25);
    this->_fontArr[WIN_FAIL_FONT] = TTF_OpenFont("./DLIB1/resources/pricedown.black.ttf", 80);
    for(int i = 0; i < FONTS_NBR; i++)
    {
        if (!this->_fontArr[i])
        {
            throw (ErrorException("SDL error in font loading!"));
        }
    }
    loadGameTextures();
}

eKeys   RenderSDL::keyBoardEvent() {
      while (SDL_PollEvent(&this->_event)) {
        //*************MENU_EXIT
        if (this->_event.type == SDL_QUIT || (this->_event.type == SDL_KEYDOWN
                                              && this->_event.key.keysym.sym == SDLK_ESCAPE)) {
             return EXIT;
        }
        if (this->_event.type == SDL_KEYDOWN && this->_event.key.keysym.sym == SDLK_m) {
              return MENU;
        }
        if (this->_event.type == SDL_KEYDOWN && this->_event.key.keysym.sym == SDLK_RETURN) {
             return ENTER;
        }
        //**************DIRECTIONS
        if (this->_event.type == SDL_KEYDOWN && this->_event.key.keysym.sym == SDLK_UP) {
            return UP;
        } else if (this->_event.type == SDL_KEYDOWN && this->_event.key.keysym.sym == SDLK_RIGHT) {
            return RIGHT;
        } else if (this->_event.type == SDL_KEYDOWN && this->_event.key.keysym.sym == SDLK_DOWN) {

            return DOWN;
        } else if (this->_event.type == SDL_KEYDOWN && this->_event.key.keysym.sym == SDLK_LEFT) {
            return LEFT;
        }
        //*****************DLIBS
        if (this->_event.type == SDL_KEYDOWN && this->_event.key.keysym.sym == SDLK_2) {
            return DLIB2;
        } else if (this->_event.type == SDL_KEYDOWN && this->_event.key.keysym.sym == SDLK_3) {
            return DLIB3;
        }
    }
    return DEFAULT;
}

void    RenderSDL::drawTexture(eTextures type, int x, int y) {

    if (type > TEXTURE_NBR || type < 0)
        return;
    SDL_Rect place = {x * SPRITE_SIZE, y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    SDL_RenderCopy(this->_renderer, this->_textArr[type], NULL, &place);
}

void    RenderSDL::drawRotTexture(eTextures type, int x, int y, eDirection direction) {

    if (type > TEXTURE_NBR || type < 0 || direction > DIRECTION_NBR || direction < 0)
        return;
    SDL_Rect place = {x * SPRITE_SIZE, y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    SDL_RenderCopyEx(this->_renderer, this->_textArr[type], NULL, &place, this->_s_map_directionDegree[direction], NULL, SDL_FLIP_NONE);
}

void    RenderSDL::clearWindow() {

    SDL_RenderClear(this->_renderer);
}

void    RenderSDL::updateWindow() {

    SDL_RenderPresent(this->_renderer);
}

SDL_Texture*    RenderSDL::loadTexture(std::string &path) {

    SDL_Texture*    text = NULL;
    SDL_Surface*    textSurface = NULL;

    if (!(textSurface = IMG_Load(path.c_str())) || !(text = SDL_CreateTextureFromSurface(this->_renderer,textSurface)))
        throw (ErrorException("Error in SDL to load texture from: " + path));
    SDL_FreeSurface(textSurface);
    return (text);
}

void    RenderSDL::loadGameTextures() {

    for(int i = SNAKE_HEAD; i < TEXTURE_NBR; i++)
        this->_textArr[i] = loadTexture(_s_map_texturePath[eTextures(i)]);
}

void    RenderSDL::renderText(std::string text, int x, int y, eFonts font, eColors color) {

    if (font < 0 || font > FONTS_NBR)
        return;
    SDL_Surface     *textSurface = TTF_RenderText_Solid(_fontArr[font], text.c_str(), _colorsArr[color]);
    SDL_Rect place = {x * SPRITE_SIZE, y * SPRITE_SIZE, textSurface->w, textSurface->h};
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(this->_renderer, textTexture, NULL, &place);
    SDL_DestroyTexture(textTexture);
}

int     RenderSDL::imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;

extern "C" IRender* create() {
    return (new RenderSDL());
}

extern "C" void destroy(IRender *render) {
   delete render;
   render = nullptr;
}
