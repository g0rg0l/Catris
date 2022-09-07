#include "I.h"

I::I(sf::Vector2f pos) : Figure()
{
    name = 'I';
    if (pos == sf::Vector2f(0, 0))
    {
        figurePosition = sf::Vector2f (30 + ((rand() % 10) * 30),30);
    }
    else figurePosition = pos;

    Square part1(figurePosition, figurePartsSize, figureColor, 2);
    Square part2(sf::Vector2f(figurePosition.x, figurePosition.y + figurePartsSize),
                 figurePartsSize, figureColor, 2);
    Square part3(sf::Vector2f(figurePosition.x, figurePosition.y + 2*figurePartsSize),
                 figurePartsSize, figureColor, 2);
    Square part4(sf::Vector2f(figurePosition.x, figurePosition.y + 3*figurePartsSize),
                 figurePartsSize, figureColor, 2);

    figureParts.push_back(part1);
    figureParts.push_back(part2);
    figureParts.push_back(part3);
    figureParts.push_back(part4);
}