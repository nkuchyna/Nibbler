//
// Created by Nadiia KUCHYNA on 2019-01-24..
//
#include "RenderOpenGL.h"

char      keyOnce[GLFW_KEY_LAST + 1];
#define KeyPressedOnce(WINDOW, KEY) (glfwGetKey(WINDOW, KEY) ?\
                                    (keyOnce[KEY] ? false : (keyOnce[KEY] = true)) : (keyOnce[KEY] = false))

RenderOpenGl::RenderOpenGl() {
    init();
}

RenderOpenGl::RenderOpenGl(RenderOpenGl const &src) {
    *this = src;
}

RenderOpenGl & RenderOpenGl::operator=(RenderOpenGl const &src) {
    if(&src != this)
    {
        glfwDestroyWindow(_window);
        this->_window = src._window;
        for(int i = 0; i < FONTS_NBR; i++)
        {
            if(this->_fontsArr[i])
                delete this->_fontsArr[i];
            if(src._fontsArr[i])
                this->_fontsArr[i] = src._fontsArr[i];
        }
        for(int i = 0; i < TEXTURE_NBR; i++)
        {
            if(this->_texturesArr[i])
                delete this->_texturesArr[i];
            if(src._texturesArr[i])
                this->_texturesArr[i] = src._texturesArr[i];
        }
        if (this->_shader){
            delete this->_shader;
            this->_shader = src._shader;
        }
        this->_s_map_texturePath.clear();
        this->_s_map_texturePath.insert(src._s_map_texturePath.begin(), src._s_map_texturePath.end());
        this->_s_map_directionDegree.clear();
        this->_s_map_directionDegree.insert(src._s_map_directionDegree.begin(), src._s_map_directionDegree.end());
        this->_s_map_fontSizes.clear();
        this->_s_map_fontSizes.insert(src._s_map_fontSizes.begin(), src._s_map_fontSizes.end());
    }
    return (*this);
}

RenderOpenGl::~RenderOpenGl() {

    for(int i = 0; i < FONTS_NBR; i++)
    {
        if(this->_fontsArr[i])
            delete this->_fontsArr[i];
    }
     for(int i = 0; i < TEXTURE_NBR; i++)
    {
        if(this->_texturesArr[i])
            delete this->_texturesArr[i];
    }
    if (this->_shader)
        delete this->_shader;
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void    RenderOpenGl::init() {

    //*************Init textures_paths
    this->_s_map_texturePath[SNAKE_HEAD] = "./DLIB3/resources/snake_head.png";
    this->_s_map_texturePath[SNAKE_BODY] = "./DLIB3/resources/snake_body.png";
    this->_s_map_texturePath[SNAKE_BODY_LEFT] = "./DLIB3/resources/snake_body_left.png";
    this->_s_map_texturePath[SNAKE_BODY_RIGHT] = "./DLIB3/resources/snake_body_right.png";
    this->_s_map_texturePath[SNAKE_TAIL] = "./DLIB3/resources/snake_tail.png";
    this->_s_map_texturePath[SNAKE_TAIL_LEFT] = "./DLIB3/resources/snake_tail_left.png";
    this->_s_map_texturePath[SNAKE_TAIL_RIGHT] = "./DLIB3/resources/snake_tail_right.png";
    this->_s_map_texturePath[SNAKE_HEAD_DEAD] = "./DLIB3/resources/snake_head_death.png";
    this->_s_map_texturePath[SNAKE_BODY_DEAD] = "./DLIB3/resources/snake_body_death.png";
    this->_s_map_texturePath[SNAKE_BODY_LEFT_DEAD] = "./DLIB3/resources/snake_body_left_death.png";
    this->_s_map_texturePath[SNAKE_BODY_RIGHT_DEAD] = "./DLIB3/resources/snake_body_right_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_DEAD] = "./DLIB3/resources/snake_tail_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_LEFT_DEAD] = "./DLIB3/resources/snake_tail_left_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_RIGHT_DEAD] = "./DLIB3/resources/snake_tail_right_death.png";
    this->_s_map_texturePath[APPLE_TEXT] = "./DLIB3/resources/apple.png";
    this->_s_map_texturePath[OBSTACLE_TEXT] = "./DLIB3/resources/obstacle3.png";
    this->_s_map_texturePath[FRAME_TEXT] = "./DLIB3/resources/frame.png";
    this->_s_map_texturePath[BOARD] = "./DLIB3/resources/board_game.png";
    this->_s_map_texturePath[MAIN_BOARD] = "./DLIB3/resources/board.png";
    this->_s_map_texturePath[SUPER_APPLE_TEXT] = "./DLIB3/resources/supper_apple.png";

    //*************Init direction rotation angle
    this->_s_map_directionDegree[NORTH] = 0;
    this->_s_map_directionDegree[EAST] = 90;
    this->_s_map_directionDegree[SOUTH] = 180;
    this->_s_map_directionDegree[WEST] = 270;

    this->_s_map_fontSizes[MENU_FONT] = 90;
    this->_s_map_fontSizes[GAME_FONT] = 64;
    this->_s_map_fontSizes[INFO_FONT] = 50;
    this->_s_map_fontSizes[WIN_FAIL_FONT] = 160;

    if (!glfwInit())
    {
        glfwTerminate();
        throw (ErrorException("Error in glwf initialization"));
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    //*************init colors
    _colorArr[REGULAR].r =  0.36;
    _colorArr[REGULAR].g =  0.35;
    _colorArr[REGULAR].b =  0.38;

    _colorArr[HIGHLIGHT].r =  0.75;
    _colorArr[HIGHLIGHT].g =  0.77;
    _colorArr[HIGHLIGHT].b =  0.78;

    _colorArr[TEXT].r =  0.19;
    _colorArr[TEXT].g =  0.24;
    _colorArr[TEXT].b =  0.22;

    _colorArr[EXTRA].r =  0.39;
    _colorArr[EXTRA].g =  0.08;
    _colorArr[EXTRA].b =  0;
}

void RenderOpenGl::createWindow(int width, int height) {

    if (!(this->_window = glfwCreateWindow(width * SPRITE_SIZE, height * SPRITE_SIZE, "Nibbler from OpenGL", NULL, NULL)))
    {
        throw (ErrorException("Error in window initialization (GLWF/OPENGL)!"));

    }
    this->_height = height;
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(_window, (mode->width - width * SPRITE_SIZE) / 2, (mode->height - height * SPRITE_SIZE) / 2);
    glfwGetFramebufferSize(_window, &_bufferWidth, &_bufferHeight);
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(_window);
        throw (ErrorException("Error in GLEW initialization (GLWF/OPENGL)!"));
    }
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glViewport(0, 0, _bufferWidth, _bufferHeight);
    //creating shader
    try {
        this->_shader = new Shader("./DLIB3/resources/basicShader");
    }
    catch (std::bad_alloc& ba)
    {
        throw (ErrorException("The memory was not allocated for OpenGL shader or texture"));
    }
    loadGameTextures();
    //*************Init fonts
    try {
        _fontsArr[MENU_FONT] = new FTGLPixmapFont("./DLIB3/resources/pricedown.black.ttf");
        _fontsArr[GAME_FONT] = new FTGLPixmapFont("./DLIB3/resources/alba.super.ttf");
        _fontsArr[INFO_FONT] = new FTGLPixmapFont("./DLIB3/resources/OpenSans.ttf");
        _fontsArr[WIN_FAIL_FONT] = new FTGLPixmapFont("./DLIB3/resources/pricedown.black.ttf");
    }
    catch (std::bad_alloc& ba)
    {
        throw (ErrorException("The memory was not allocated for OpenGL font"));
    }
    for (int i = 0; i < FONTS_NBR; i++)
    {
        if(_fontsArr[i]->Error())
        {
            throw (ErrorException("Error in OpenGL to font download"));
        }
    }
    //init view projection
    this->_renderer.init(width * SPRITE_SIZE, height * SPRITE_SIZE);
    this->_renderer.initShader(_shader);
}

eKeys RenderOpenGl::keyBoardEvent() {

    glfwPollEvents();
    if(KeyPressedOnce(_window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(_window))
        return EXIT;
    else if (KeyPressedOnce(_window, GLFW_KEY_M)) {
            return MENU;
    }
    else if (KeyPressedOnce(_window, GLFW_KEY_UP) == GLFW_PRESS) {
        return UP;
    }
    else if (KeyPressedOnce(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        return RIGHT;
    }
    else if (KeyPressedOnce(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        return DOWN;
    }
    else if (KeyPressedOnce(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
           return LEFT;
    }
    else if (KeyPressedOnce(_window, GLFW_KEY_1) == GLFW_PRESS) {
        return DLIB1;
    }
    else if (KeyPressedOnce(_window, GLFW_KEY_2) == GLFW_PRESS) {
        return DLIB2;
    }
    else if (KeyPressedOnce(_window, GLFW_KEY_ENTER) == GLFW_PRESS) {
         return ENTER;
    }
    return DEFAULT;
}

void    RenderOpenGl::drawTexture(eTextures type, int x, int y) {

    this->_renderer.bindShader();
    this->_renderer.drawSprite(_texturesArr[type], glm::vec2(x * SPRITE_SIZE, y * SPRITE_SIZE), glm::vec2(SPRITE_SIZE, SPRITE_SIZE), 0.0f);
}

void    RenderOpenGl::drawRotTexture(eTextures type, int x, int y, eDirection direction) {

    this->_renderer.bindShader();
    this->_renderer.drawSprite(_texturesArr[type], glm::vec2(x * SPRITE_SIZE , y * SPRITE_SIZE), glm::vec2(SPRITE_SIZE, SPRITE_SIZE), _s_map_directionDegree[direction] * 3.14 / 180);
}

void    RenderOpenGl::clearWindow() {

    glClearColor(0.60f, 0.60f, 0.60f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void    RenderOpenGl::updateWindow() {

    glfwSwapBuffers(_window);
}

void    RenderOpenGl::renderText(std::string text, int x, int y, eFonts font, eColors color) {

    if (font < 0 || font > FONTS_NBR || color < 0 || color > COLORS_NBR)
        return;

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);

    FTPoint coord(x * SPRITE_SIZE * 2, (_height - y - 1) * SPRITE_SIZE * 2, 0);
    glPixelTransferf(GL_RED_BIAS, _colorArr[color].r - 1.0f);
    glPixelTransferf(GL_GREEN_BIAS, _colorArr[color].g - 1.0f);
    glPixelTransferf(GL_BLUE_BIAS, _colorArr[color].b - 1.0f);

    _fontsArr[font]->FaceSize(_s_map_fontSizes[font]);
    _fontsArr[font]->Render(text.c_str(), text.size() , coord);
    glPixelTransferf(GL_RED_BIAS, 0.0f);
    glPixelTransferf(GL_GREEN_BIAS, 0.0f);
    glPixelTransferf(GL_BLUE_BIAS, 0.0f);

}

void    RenderOpenGl::loadGameTextures() {

    for(int i = 0; i < TEXTURE_NBR; i++)
        this->_texturesArr[i] = new Texture(_s_map_texturePath[static_cast<eTextures>(i)]);
}

extern "C" IRender* create() {
    return (new RenderOpenGl());
}

extern "C" void destroy(IRender *render) {
    delete render;
    render = nullptr;
}
