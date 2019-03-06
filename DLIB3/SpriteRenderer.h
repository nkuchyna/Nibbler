//
// Created by Nadiia KUCHYNA on 2019-01-25.
//

#ifndef NIBLER_SPRITERENDERER_H
#define NIBLER_SPRITERENDERER_H
#define GLM_FORCE_SILENT_WARNINGS
#include<glm/glm.hpp>
#include <GL/glew.h>
#include "Shader.h"
#include "Texture.h"

class   SpriteRenderer
{
public:
    SpriteRenderer();
    ~SpriteRenderer();
    SpriteRenderer(const SpriteRenderer &obj);
    SpriteRenderer& operator=(const SpriteRenderer &obj);

    void    initShader(Shader *shaderPtr);
    void    bindShader();
    void    init(int width, int height);
    void    drawSprite(Texture *texture, glm::vec2 position, glm::vec2 size, GLfloat rotate);

private:
    Shader      *_shader;
    GLuint      _VAO;
    glm::mat4   _projection;

};

#endif //NIBLER_SPRITERENDERER_H
