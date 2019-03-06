//
// Created by Vyachealav MARTYNUIK on 2019-01-16.
//
#include "RenderSFML.h"

RenderSFML::RenderSFML() {
    init();
}

RenderSFML::RenderSFML(RenderSFML const &src) {
    *this = src;
}

RenderSFML & RenderSFML::operator=(RenderSFML const &src) {
   if(&src != this)
   {
       _window->close();
       this->_window = src._window;
       this->_event = src._event;
       for(int i = 0; i < TEXTURE_NBR; i++)
           this->_texturesArr[i] = src._texturesArr[i];
       for(int i = 0; i < FONTS_NBR; i++)
           this->_fontArr[i] = src._fontArr[i];
       for(int i = 0; i < COLORS_NBR; i++)
           this->_colorsArr[i] = src._colorsArr[i];
       this->_s_map_texturePath.clear();
       this->_s_map_texturePath.insert(src._s_map_texturePath.begin(), src._s_map_texturePath.end());
       this->_s_map_fontPath.clear();
       this->_s_map_fontPath.insert(src._s_map_fontPath.begin(), src._s_map_fontPath.end());
       this->_s_map_fontSizes.clear();
       this->_s_map_fontSizes.insert(src._s_map_fontSizes.begin(), src._s_map_fontSizes.end());
       this->_s_map_directionDegree.clear();
       this->_s_map_directionDegree.insert(src._s_map_directionDegree.begin(), src._s_map_directionDegree.end());
   }
    return (*this);
}

RenderSFML::~RenderSFML() {
    _window->close();
    delete _window;
}

void    RenderSFML::init() {

//*************Init textures_paths
    this->_s_map_texturePath[SNAKE_HEAD] = "./DLIB2/resources/snake_head.png";
    this->_s_map_texturePath[SNAKE_BODY] = "./DLIB2/resources/snake_body.png";
    this->_s_map_texturePath[SNAKE_BODY_LEFT] = "./DLIB2/resources/snake_body_left.png";
    this->_s_map_texturePath[SNAKE_BODY_RIGHT] = "./DLIB2/resources/snake_body_right.png";
    this->_s_map_texturePath[SNAKE_TAIL] = "./DLIB2/resources/snake_tail.png";
    this->_s_map_texturePath[SNAKE_TAIL_LEFT] = "./DLIB2/resources/snake_tail_left.png";
    this->_s_map_texturePath[SNAKE_TAIL_RIGHT] = "./DLIB2/resources/snake_tail_right.png";
    this->_s_map_texturePath[SNAKE_HEAD_DEAD] = "./DLIB2/resources/snake_head_death.png";
    this->_s_map_texturePath[SNAKE_BODY_DEAD] = "./DLIB2/resources/snake_body_death.png";
    this->_s_map_texturePath[SNAKE_BODY_LEFT_DEAD] = "./DLIB2/resources/snake_body_left_death.png";
    this->_s_map_texturePath[SNAKE_BODY_RIGHT_DEAD] = "./DLIB2/resources/snake_body_right_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_DEAD] = "./DLIB2/resources/snake_tail_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_LEFT_DEAD] = "./DLIB2/resources/snake_tail_left_death.png";
    this->_s_map_texturePath[SNAKE_TAIL_RIGHT_DEAD] = "./DLIB2/resources/snake_tail_right_death.png";
    this->_s_map_texturePath[APPLE_TEXT] = "./DLIB2/resources/apple.png";
    this->_s_map_texturePath[OBSTACLE_TEXT] = "./DLIB2/resources/obstacle.png";
    this->_s_map_texturePath[FRAME_TEXT] = "./DLIB2/resources/frame.png";
    this->_s_map_texturePath[BOARD] = "./DLIB2/resources/game_board.png";
    this->_s_map_texturePath[MAIN_BOARD] = "./DLIB2/resources/board.png";
    this->_s_map_texturePath[SUPER_APPLE_TEXT] = "./DLIB2/resources/supper_apple.png";

    //*************Init direction rotation angle
    this->_s_map_directionDegree[NORTH] = 0;
    this->_s_map_directionDegree[EAST] = 90;
    this->_s_map_directionDegree[SOUTH] = 180;
    this->_s_map_directionDegree[WEST] = 270;

    //************Init fonts paths
    this->_s_map_fontPath[MENU_FONT] = "./DLIB2/resources/pricedown.black.ttf";
    this->_s_map_fontPath[GAME_FONT] = "./DLIB2/resources/alba.super.ttf";
    this->_s_map_fontPath[INFO_FONT] = "./DLIB2/resources/OpenSans.ttf";
    this->_s_map_fontPath[WIN_FAIL_FONT] = "./DLIB2/resources/pricedown.black.ttf";

    this->_colorsArr[REGULAR] = sf::Color(123, 127, 137, 255);
    this->_colorsArr[HIGHLIGHT] = sf::Color(200, 100, 39, 255);
    this->_colorsArr[TEXT] = sf::Color(79, 96, 202, 255);
    this->_colorsArr[EXTRA] = sf::Color(148, 66, 15, 255);

    this->_s_map_fontSizes[MENU_FONT] = 90;
    this->_s_map_fontSizes[GAME_FONT] = 64;
    this->_s_map_fontSizes[INFO_FONT] = 50;
    this->_s_map_fontSizes[WIN_FAIL_FONT] = 160;
}

void RenderSFML::createWindow(int width, int height) {

    sf::ContextSettings settings;
    try {
        _window = new sf::RenderWindow(sf::VideoMode(width * SPRITE_SIZE, height * SPRITE_SIZE), "Nibbler from SFML",
                                       sf::Style::Default);
    }
    catch (std::bad_alloc& ba)
    {
        throw (ErrorException("The memory was not allocated for SFML window"));
    }
    _window->setView(_window->getDefaultView());
    auto desktop = sf::VideoMode::getDesktopMode();
    _window->setPosition(sf::Vector2i(desktop.width/2 - _window->getSize().x/2, desktop.height/2 - _window->getSize().y/2));
    _window->setKeyRepeatEnabled(false);
    loadGameFonts();
    loadGameTextures();
}

eKeys RenderSFML::keyBoardEvent() {

    while (_window->pollEvent(_event)) {
        //*************MENU_EXIT
        if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return EXIT;

        if (sf::Event::KeyPressed && _event.key.code == sf::Keyboard::M) {
            return MENU;
        }
        if (sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Return) {
            return ENTER;
        }
        //**************DIRECTIONS
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            return UP;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            return RIGHT;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            return DOWN;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            return LEFT;
        }
        //*****************DLIBS
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            return DLIB1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            return DLIB3;
        }
    }
    return DEFAULT;
}

void    RenderSFML::drawTexture(eTextures type, int x, int y) {

    sf::Sprite      sprite;

    sprite.setTexture(_texturesArr[type]);
    sprite.setPosition(sf::Vector2f(x * SPRITE_SIZE, y * SPRITE_SIZE));
    _window->draw(sprite);
}

void    RenderSFML::drawRotTexture(eTextures type, int x, int y, eDirection direction) {

    sf::Sprite      sprite;

    sprite.setTexture(_texturesArr[type]);
    sprite.setOrigin(SPRITE_SIZE/ 2, SPRITE_SIZE / 2);
    sprite.setRotation(_s_map_directionDegree[direction]);
    sprite.setPosition(sf::Vector2f(x * SPRITE_SIZE + SPRITE_SIZE / 2, y * SPRITE_SIZE + SPRITE_SIZE/ 2));
    _window->draw(sprite);
}

void    RenderSFML::clearWindow() {

    _window->clear(sf::Color(22, 28, 77, 255));
}

void    RenderSFML::updateWindow() {

    _window->display();
}

void    RenderSFML::renderText(std::string text, int x, int y, eFonts font, eColors color) {

    if (font < 0 || font > FONTS_NBR || color < 0 || color > COLORS_NBR)
        return;
    sf::Text sfText;
    sfText.setFont(this->_fontArr[font]);
    sfText.setString(text.c_str());
    sfText.setCharacterSize(this->_s_map_fontSizes[font]);
    sfText.setFillColor(this->_colorsArr[color]);
    sfText.setPosition(sf::Vector2f(x * SPRITE_SIZE, y * SPRITE_SIZE));
    _window->draw(sfText);
}

void    RenderSFML::loadGameTextures() {

    for(int i = 0; i < TEXTURE_NBR; i++)
    {
        if(!(this->_texturesArr[i].loadFromFile(_s_map_texturePath[static_cast<eTextures>(i)])))
            throw (ErrorException("Error in SFML to load texture from: "+ _s_map_texturePath[(eTextures)i]));
    }
}

void    RenderSFML::loadGameFonts() {

    for(int i = 0; i < FONTS_NBR; i++)
    {
        if (!(this->_fontArr[i].loadFromFile(_s_map_fontPath[static_cast<eFonts>(i)])))
            throw (ErrorException("Error in SFML to load font from: "+ _s_map_fontPath[(eFonts)i]));

    }
}

extern "C" IRender* create() {
    return (new RenderSFML());
}

extern "C" void destroy(IRender *render) {
    delete render;
    render = nullptr;
}
