#ifndef TETRIS_ENGINE_H
#define TETRIS_ENGINE_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Objects.h"
#include "ResourceHolder.h"

class Engine
{
public:
    Engine();
    void runEngine();

private:
    void pollEvents();
    void checkForMove();

    void update();

    void draw();
    void loadDesignElements();

private:
    sf::RenderWindow window;
    sf::Font titleFont;

    float spentTime = 0;
    float keyboardTime = 0;
    sf::Clock clock;

    Objects objects;

    std::vector<sf::RectangleShape> designElements;
    std::vector<sf::RectangleShape> grid;
    std::vector<sf::Text> text;
    sf::Text scoreText;
    sf::Text lineCountText;

};


#endif //TETRIS_ENGINE_H
