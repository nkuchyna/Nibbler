//
// Created by Nadiia KUCHYNA on 2019-01-25.
//

#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer() {}

SpriteRenderer::~SpriteRenderer() {}

SpriteRenderer::SpriteRenderer(const SpriteRenderer &obj) {
    *this = obj;
}

SpriteRenderer& SpriteRenderer::operator=(const SpriteRenderer &obj) {

    if (&obj != this)
    {
        delete  this->_shader;
        this->_shader = obj._shader;
        this->_VAO = obj._VAO;
        this->_projection = obj._projection;
    }
    return (*this);
}

void    SpriteRenderer::initShader(Shader *shaderPtr) {

    this->_shader = shaderPtr;
}

void    SpriteRenderer::bindShader() {

    this->_shader->bindShader();
}

void    SpriteRenderer::init(int width, int height) {

    GLuint VBO;
    GLfloat vertices[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->_VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->_VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //init projection
    this->_projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

}

void    SpriteRenderer::drawSprite(Texture *texture, glm::vec2 position, glm::vec2 size, GLfloat rotate) {

    //calculate sprite model
    glm::mat4   spriteModel = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };
    spriteModel = glm::translate(spriteModel, glm::vec3(position, 0.0f));
    spriteModel = glm::translate(spriteModel, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    spriteModel = glm::rotate(spriteModel, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    spriteModel = glm::translate(spriteModel, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    spriteModel = glm::scale(spriteModel, glm::vec3(size, 1.0f));
    this->_shader->updateShader(spriteModel, this->_projection);

    texture->bindTexture();
    glBindVertexArray(this->_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
