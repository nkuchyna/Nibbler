//
// Created by Nadiia KUCHYNA on 2019-01-24..
//

#ifndef NIBLER_RENDEROPENGL_H
#define NIBLER_RENDEROPENGL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <freetype2/ft2build.h>

#include "IRender.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteRenderer.h"

#define SPRITE_SIZE 32

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

class RenderOpenGl  : public IRender {

public:

    RenderOpenGl();
    RenderOpenGl(RenderOpenGl const &);
    RenderOpenGl &operator=(RenderOpenGl const &);
    ~RenderOpenGl();

    void    createWindow(int width, int height) override;
    eKeys   keyBoardEvent() override;
    void    drawTexture(eTextures type, int x, int y) override;
    void    drawRotTexture(eTextures type, int x, int y, eDirection direction) override;
    void    clearWindow() override;
    void    updateWindow() override;
    void    renderText(std::string text, int x, int y, eFonts font, eColors color) override;

private:

    void                init();
    GLFWwindow           *_window;
    int                 _bufferWidth;
    int                 _bufferHeight;
    int                 _height;

    Shader              *_shader;
    Texture*            _texturesArr[TEXTURE_NBR];
    FTGLPixmapFont      *_fontsArr[FONTS_NBR];
    Color               _colorArr[COLORS_NBR];
    SpriteRenderer      _renderer;

    void                loadGameTextures();

    std::map<eTextures, std::string>    _s_map_texturePath;
    std::map<eDirection, double>        _s_map_directionDegree;
    std::map<eFonts, int>               _s_map_fontSizes;
};

#endif //NIBLER_RENDEROPENGL_H
