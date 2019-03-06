//
// Created by Nadiia KUCHYNA on 2019-01-24.
//

#include "Shader.h"
#include "ErrorException.h"

Shader::Shader(const std::string &fileName) {

    _program = glCreateProgram();
    _shaders[VERTEX] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    _shaders[FRAGMENT] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for(int i = 0; i < NUM_SHADERS; i++)
    {
        glAttachShader(_program, _shaders[i]);
    }
    glLinkProgram(_program);
    checkShader(_program, GL_LINK_STATUS, true, "Program linking failed! ->");
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glValidateProgram(_program);
    checkShader(_program, GL_VALIDATE_STATUS, true, "Program validation failed! ->" );
    glDeleteVertexArrays(1, &vao);
    _uniforms[TRANSFORM_U] = glGetUniformLocation(_program, "transform");
}

Shader::~Shader() {

    for(int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(_program, _shaders[i]);
        glDeleteShader(_shaders[i]);
    }
    glDeleteProgram(_program);
}

void    Shader::bindShader() {

    glUseProgram(_program);
}

void    Shader::updateShader(glm::mat4 spriteModel, glm::mat4 projection)
{
    glm::mat4   model = projection * spriteModel;

    glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

GLuint  Shader::createShader(const std::string& shaderText, GLenum shaderType)
{
    GLuint  shader = glCreateShader(shaderType);

    if(shader == 0)
        throw (ErrorException("Shader was not created (OpenGL)"));

    const GLchar*   shaderSourceString[1];
    GLint           shaderSourceStringLengths[1];
    
    shaderSourceString[0] = shaderText.c_str();
    shaderSourceStringLengths[0] = shaderText.length();

    glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLengths);
    glCompileShader(shader);
    checkShader(shader, GL_COMPILE_STATUS, false, "Error in compilation of shader! ->");
    return shader;
}

std::string Shader::loadShader(const std::string &fileName) {

    std::ifstream   file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        throw (ErrorException("Unable to load shader from " + fileName));
    }
    return output;
}

void    Shader::checkShader(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {

    GLint success = 0;
    GLchar error[1024] = {0};
    int i = 0;

    if (errorMessage == "YoYoYo")
        i++;
    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);
    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        //std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
