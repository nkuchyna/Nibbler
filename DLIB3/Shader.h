//
// Created by Nadiia KUCHYNA on 2019-01-24.
//

#ifndef NIBLER_SHADER_H
#define NIBLER_SHADER_H
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

class Shader
{
public:
    Shader() = delete;
    Shader(const std::string &fileName);
    ~Shader();
    Shader(const Shader &obj) = delete;
    Shader&     operator=(const Shader &obj) = delete;

    void    bindShader();
    void    updateShader(glm::mat4 spriteModel, glm::mat4 projection);

private:
    enum
    {
        TRANSFORM_U,
        NUM_UNIFORMS
    };

    enum    eShaders
    {
        VERTEX,
        FRAGMENT,
        NUM_SHADERS
    };

    GLuint  _program;
    GLuint  _shaders[NUM_SHADERS];
    GLuint  _uniforms[NUM_UNIFORMS];

    void            checkShader(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    std::string     loadShader(const std::string &fileName);
    GLuint          createShader(const std::string& shaderText, GLenum shaderType);
};

#endif //NIBLER_SHADER_H
