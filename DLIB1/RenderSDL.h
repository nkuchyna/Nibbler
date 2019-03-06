//
// Created by Vyachealav MARTYNUIK on 2019-01-14.
//

#ifndef NIBLER_RENDER_H
#define NIBLER_RENDER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "IRender.h"
#include <map>

#define SPRITE_SIZE 32

class RenderSDL : public IRender {

public:

    RenderSDL();
    RenderSDL(RenderSDL const &);
    RenderSDL &operator=(RenderSDL const &);
    ~RenderSDL();

    void    createWindow(int width, int height) override;
    eKeys   keyBoardEvent() override;
    void    drawTexture(eTextures type, int x, int y) override;
    void    drawRotTexture(eTextures type, int x, int y, eDirection direction) override;
    void    clearWindow() override;
    void    updateWindow() override;
    void    renderText(std::string text, int x, int y, eFonts font, eColors color) override;

private:
    SDL_Window          *_window;
    SDL_Event           _event;
    SDL_Renderer        *_renderer;

    SDL_Texture*    _textArr[TEXTURE_NBR];
    TTF_Font*       _fontArr[FONTS_NBR];
    SDL_Color       _colorsArr[COLORS_NBR];

    void            init_();
    SDL_Texture*    loadTexture(std::string &path);
    void            loadGameTextures();

    std::map<eTextures, std::string>    _s_map_texturePath;
    std::map<eDirection, double>        _s_map_directionDegree;

    static int      imgFlags;
};

#endif //NIBLER_RENDER_H
