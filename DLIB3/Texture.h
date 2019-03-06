//
// Created by Nadiia KUCHYNA on 2019-01-25.
//

#ifndef NIBLER_TEXTURE_H
#define NIBLER_TEXTURE_H

#include <GL/glew.h>
#include <iostream>

class Texture
{
public:
    Texture() = delete;
    Texture(std::string &texturePath);
    ~Texture();
    Texture(const Texture &obj) = delete;
    Texture& operator=(const Texture &obj) = delete;

    void    bindTexture();
    void    unbindTexture();

private:
    GLuint  _texture;
    int     _width;
    int     _height;
    int     _componentsNbr;

    void    loadTexture(std::string &texturePath);
    void    clearTexture();
};

#endif //NIBLER_TEXTURE_H
