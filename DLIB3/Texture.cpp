//
// Created by Nadiia KUCHYNA on 2019-01-25.
//

#include "stb_image.c"
#include "ErrorException.h"
#include "Texture.h"

Texture::Texture(std::string &texturePath) {
    loadTexture(texturePath);
}

Texture::~Texture() {
    clearTexture();
}

void    Texture::loadTexture(std::string &texturePath) {

    unsigned char* imageData = stbi_load(texturePath.c_str(), &_width, &_height, &_componentsNbr, 4);
    if(imageData == NULL)
    {
        throw (ErrorException("Texture does not load from " + texturePath));
    }
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    stbi_image_free(imageData);
}

void    Texture::bindTexture() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void    Texture::unbindTexture() {

    glBindTexture(GL_TEXTURE_2D, 0);
}

void    Texture::clearTexture() {

    glDeleteTextures(1, &_texture);
    _texture = 0;
    _width = 0;
    _height = 0;
    _componentsNbr = 0;
}
