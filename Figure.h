#ifndef TETRIS_FIGURE_H
#define TETRIS_FIGURE_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "sysinfoapi.h"

#include "Square.h"

class Figure : public sf::Drawable
{

public:
    Figure()
    {
        figureColor = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    }

    void makeCopy(Figure* figure);

    /* Отрисовка */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void move(const std::string& direction, unsigned int** table);
    bool canWeMove(const std::string& direction, unsigned int** table);

    /* Общение с FigurePartsHolder'ом */
    void uploadFigureParts(std::vector<Square> &holder, unsigned int** table); // Выгрузка своих parts в хранилище

    /* Обработка столкновений */
    bool floorIntersection(unsigned int** table);

public:
    sf::Vector2f getPosition() const {return figurePosition;}
    void move(sf::Vector2f to);
    bool isMovingDown = false;
    float figurePartsSize = 30;

    sf::Vector2f getSize();

    char getName() const {return name;}

protected:
    sf::Vector2f figurePosition;
    char name;

protected:
    sf::Color figureColor;

    std::vector<Square> figureParts;
};


#endif //TETRIS_FIGURE_H
