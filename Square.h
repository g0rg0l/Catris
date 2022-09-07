#ifndef TETRIS_SQUARE_H
#define TETRIS_SQUARE_H

#include "SFML/Graphics.hpp"

class Square : public sf::Drawable
{
public:
    explicit Square(sf::Vector2f position = {}, float size = 0, sf::Color color = sf::Color::White, float borderWidth = 0.f);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void move(sf::Vector2f to);

    sf::Vector2f getPosition() {return position;}
    void SetPosition(sf::Vector2f newPosition);
    void setFillColor(sf::Color color) {squareShape.setFillColor(color);}

private:
    sf::Vector2f position;
    sf::RectangleShape squareShape;
    sf::RectangleShape lineUp;
    sf::RectangleShape lineDown;
    sf::RectangleShape lineLeft;
    sf::RectangleShape lineRight;
};


#endif //TETRIS_SQUARE_H
