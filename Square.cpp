#include "Square.h"

Square::Square(const sf::Vector2f position, const float size, const sf::Color color, const float borderWidth)
: position(position)
{
    squareShape.setSize(sf::Vector2f(size, size));
    squareShape.setFillColor(color);
    squareShape.setPosition(position);

    lineUp.setSize(sf::Vector2f(size, borderWidth));
    lineUp.setFillColor(sf::Color::White);
    lineUp.setPosition(position);

    lineDown.setSize(sf::Vector2f(size, borderWidth));
    lineDown.setFillColor(sf::Color::White);
    lineDown.setPosition(sf::Vector2f(position.x, position.y + size - borderWidth));

    lineLeft.setSize(sf::Vector2f(borderWidth, size));
    lineLeft.setFillColor(sf::Color::White);
    lineLeft.setPosition(position);

    lineRight.setSize(sf::Vector2f(borderWidth, size));
    lineRight.setFillColor(sf::Color::White);
    lineRight.setPosition(sf::Vector2f(position.x + size - borderWidth, position.y));

}

void Square::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(squareShape, states);
    target.draw(lineUp, states);
    target.draw(lineDown, states);
    target.draw(lineLeft, states);
    target.draw(lineRight, states);
}

void Square::move(sf::Vector2f to)
{
    squareShape.move(to);
    lineRight.move(to);
    lineLeft.move(to);
    lineUp.move(to);
    lineDown.move(to);

    position = squareShape.getPosition();
}

void Square::SetPosition(sf::Vector2f newPosition)
{
    squareShape.setPosition(newPosition);
    lineRight.setPosition(newPosition);
    lineLeft.setPosition(newPosition);
    lineUp.setPosition(newPosition);
    lineDown.setPosition(newPosition);

    position = newPosition;
}
