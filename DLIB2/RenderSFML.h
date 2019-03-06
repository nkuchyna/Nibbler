//
// Created by Vyachealav MARTYNUIK on 2019-01-16.
//

#ifndef NIBLER_RENDERSFML_H
#define NIBLER_RENDERSFML_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "IRender.h"

#define SPRITE_SIZE 64

class RenderSFML  : public IRender {

public:

    RenderSFML();
    RenderSFML(RenderSFML const &);
    RenderSFML &operator=(RenderSFML const &);
    ~RenderSFML();

    void    createWindow(int width, int height) override;
    eKeys   keyBoardEvent() override;
    void    drawTexture(eTextures type, int x, int y) override;
    void    drawRotTexture(eTextures type, int x, int y, eDirection direction) override;
    void    clearWindow() override;
    void    updateWindow() override;
    void    renderText(std::string text, int x, int y, eFonts font, eColors color) override;

private:
    sf::RenderWindow    *_window;
    sf::Event           _event;
    sf::Texture         _texturesArr[TEXTURE_NBR];
    sf::Font            _fontArr[FONTS_NBR];
    sf::Color           _colorsArr[COLORS_NBR];

    void                init();
    void                loadGameTextures();
    void                loadGameFonts();

    std::map<eTextures, std::string>    _s_map_texturePath;
    std::map<eFonts, std::string>       _s_map_fontPath;
    std::map<eFonts, int>               _s_map_fontSizes;
    std::map<eDirection, double>        _s_map_directionDegree;
};

#endif //NIBLER_RENDERSFML_H
