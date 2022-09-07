#include "Figure.h"

void Figure::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& part : figureParts)
    {
        target.draw(part, states);
    }
}

void Figure::move(const std::string& direction, unsigned int** table)
{
    if (direction == "down")
    {
        if (canWeMove("down", table))
        {
            move(sf::Vector2f(0, figurePartsSize));
        }
    }
    if (direction == "left")
    {
        if (canWeMove("left", table))
        {
            move(sf::Vector2f(-figurePartsSize, 0));
        }
    }
    if (direction == "right")
    {
        if (canWeMove("right", table))
        {
            move(sf::Vector2f(figurePartsSize, 0));
        }
    }
}

bool Figure::canWeMove(const std::string& direction, unsigned int** table)
{
    // Нужно перед ходом в нужное направление проверить, можем ли мы туда сдвинуться
    if (direction == "down")
    {
        bool flag = true;
        for (auto& square : figureParts)
        {
            sf::Vector2u tablePosition((
                      (unsigned int) (square.getPosition().y / figurePartsSize) - 1),
                   (unsigned int) ((square.getPosition().x / figurePartsSize) - 1)
                    );

            /* Сперва проверка на столкновение с границами Тетриса */
            if (tablePosition.x == 19)
            {
                flag = false;
                break;
            }

            /* Проверка на столкновение с другими фигурами */
            if (table[tablePosition.x + 1][tablePosition.y] == 1)
            {
                flag = false;
                break;
            }
        }

        return flag;
    }
    if (direction == "left")
    {
        bool flag = true;
        for (auto& square : figureParts)
        {
            sf::Vector2u tablePosition(
                    (unsigned int) ((square.getPosition().y / figurePartsSize) - 1),
                    (unsigned int) ((square.getPosition().x / figurePartsSize) - 1)
                    );

            /* Сперва проверка на столкновение с границами Тетриса */
            if (tablePosition.y == 0)
            {
                flag = false;
                break;
            }

            /* Проверка на столкновение с другими фигурами */
            if (table[tablePosition.x][tablePosition.y - 1] == 1)
            {
                flag = false;
                break;
            }
        }

        return flag;
    }
    if (direction == "right")
    {
        bool flag = true;
        for (auto& square : figureParts)
        {
            sf::Vector2u tablePosition(
                    (unsigned int) ((square.getPosition().y / figurePartsSize) - 1),
                    (unsigned int) ((square.getPosition().x / figurePartsSize) - 1)
                    );

            /* Сперва проверка на столкновение с границами Тетриса */
            if (tablePosition.y == 9)
            {
                flag = false;
                break;
            }

            /* Проверка на столкновение с другими фигурами */
            if (table[tablePosition.x][tablePosition.y + 1] == 1)
            {
                flag = false;
                break;
            }
        }

        return flag;
    }

    return false;
}
//

void Figure::uploadFigureParts(std::vector<Square> &holder, unsigned int** table)
{
    for (auto& square : figureParts)
    {
        sf::Vector2f partPosition = square.getPosition(); // Получаем позицию квадрата в фигуре
        sf::Vector2u tablePosition((
                                           (unsigned int) (partPosition.x / figurePartsSize) - 1),
                                   (unsigned int) ((partPosition.y / figurePartsSize) - 1)
        ); // Получаем позицию квадрата в таблице

        if (table[tablePosition.y][tablePosition.x] != 1) // Если эта позиция не занята
        {
            holder.push_back(square);
            table[tablePosition.y][tablePosition.x] = 1; // Запоминание заблокированных квадратов
        }
    }
}

bool Figure::floorIntersection(unsigned int** table)
{
    for (auto& part : figureParts)
    {
        sf::Vector2f partPosition = part.getPosition(); // Получаем позицию квадрата в фигуре
        sf::Vector2u tablePosition(
                (unsigned int) ((partPosition.x / figurePartsSize) - 1),
                (unsigned int) ((partPosition.y / figurePartsSize) - 1)
                ); // Получаем позицию квадрата в таблице

        if (tablePosition.y == 19) return true; // Достигли дна
        if (table[tablePosition.y + 1][tablePosition.x] == 1) return true; // Проверка следующей позиции в таблице, относительно текущей // достигли занятой позиции
    }

    return false;
}

void Figure::move(sf::Vector2f to)
{
    for (auto& part : figureParts) part.move(to);
    figurePosition += to;
}

sf::Vector2f Figure::getSize()
{
    float maxRight = figureParts[0].getPosition().x;
    float maxBottom = figureParts[0].getPosition().y;

    for (auto& square : figureParts)
    {
        sf::Vector2f squarePos = square.getPosition();
        if (squarePos.x > maxRight)
        {
            maxRight = squarePos.x;
        }
    }
    for (auto& square : figureParts)
    {
        sf::Vector2f squarePos = square.getPosition();
        if (squarePos.y > maxBottom)
        {
            maxBottom = squarePos.y;
        }
    }

    return {
        maxRight + 30 - figurePosition.x,
        maxBottom + 30 - figurePosition.y
    };
}

void Figure::makeCopy(Figure *figure)
{
    for (auto& square : figure->figureParts)
    {
        square.setFillColor(figureColor);
    }

//    figure->figureParts = figureParts;
    figure->figurePartsSize = figurePartsSize;
    figure->figureColor = figureColor;
    figure->name = name;
}
