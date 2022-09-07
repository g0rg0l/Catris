#include "Objects.h"

Objects::Objects()
{
    fallingFigure = generateNewFigure();
    nextFigure = generateNewFigure();
    createCopyOfNextFigure();

    table = new unsigned int*[20];
    for (int i = 0; i < 20; ++i)
    {
        table[i] = new unsigned int[10];
    }

    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 10; j++)
        {
            table[i][j] = 0;
        }
    }
}

Objects::~Objects()
{
    delete fallingFigure;
    delete nextFigure;
    delete copyOfNextFigure;

    for (int i = 0; i < 20; ++i)
    {
        delete [] table[i];
    }
    delete [] table;
}

void Objects::updateFigures(float &spentTime)
{
    /* Нужно проверить, достигла ли фигура дна */
    if (fallingFigure->floorIntersection(table))
    {
        fallingFigure->uploadFigureParts(fallenSquares, table); // Передаём parts фигуры
        delete fallingFigure; // удаляем падающую фигуру
        fallingFigure = nullptr;

        checkForLose();

        if (!lost)
        {
            fallingFigure = nextFigure;
            nextFigure = generateNewFigure();
            createCopyOfNextFigure();
        }

        accruePoint(checkForCompletedRows()); // Проверяем, есть ли закрытые строки
    }
    /* Передвигаем падающую фигуру вниз на клетку */
    if (!lost && !(fallingFigure->isMovingDown)) fallingFigure->move("down", table);
    if (!lost && !(fallingFigure->canWeMove("down", table))) spentTime = 0.6;
}

int Objects::checkForCompletedRows()
{
    int count = 0;
    for (int i = 0; i < 20; ++i)
    {
        bool flag = true;
        for (int j = 0; j < 10; ++j)
        {
            if (table[i][j] != 1)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            deleteRow(i); // Удаляем строку
            count++;
            reshapeRows(i); // Опускаем все строки выше удалённой
        }
    }

    return count;
}

void Objects::deleteRow(int i)
{
    /* Инкремент счётчика */
    lineCount++;

    /* Удаление ряда Square'ов из вектора */
    std::vector<Square> vectorToCopy;

    float yCord = (float) (i + 1) * 30;
    for (auto& square : fallenSquares)
    {
        if (square.getPosition().y != yCord) // Если square не стоит на удаляемой строке, то копируем его
        {
            vectorToCopy.push_back(square);
        }
    }
    fallenSquares = vectorToCopy;
}

void Objects::reshapeRows(int index)
{
    /* Сдвиг square'ов из вектора */
    for (int i = index - 1; i > 0; --i)
    {
        float yCord = (float) (i + 1) * 30;
        for (auto& square : fallenSquares)
        {
            if (square.getPosition().y == yCord)
            {
                square.move(sf::Vector2f(0, 30));
            }
        }
    }

    /* Сдвиг позиций в таблице */
    for (int i = index; i > 0; --i)
    {
        for (int j = 0; j < 10; ++j)
        {
            table[i][j] = table[i - 1][j];
        }
        for (int j = 0; j < 10; ++j)
        {
            table[0][j] = 0;
        }
    }
}

void Objects::checkForLose()
{
    for (int j = 0; j < 10; ++j)
    {
        if (table[0][j] == 1)
        {
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
            std::cout << "                LOSE              " << std::endl;
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
            lost = true;
            break;
        }
    }
}

Figure* Objects::generateNewFigure()
{
    const char possibleFigures[7] = {'I', 'O', 'L',
                                     'J', 'T', 'Z',
                                     'S'
                                     };

    Figure* pFallingFigure;

    switch (possibleFigures[rand() % 7])
    {
        case 'I':
            pFallingFigure = new I();
            break;
        case 'O':
            pFallingFigure = new O();
            break;
        case 'L':
            pFallingFigure = new L();
            break;
        case 'J':
            pFallingFigure = new J();
            break;
        case 'T':
            pFallingFigure = new T();
            break;
        case 'Z':
            pFallingFigure = new Z();
            break;
        case 'S':
            pFallingFigure = new S();
            break;
    }

    return pFallingFigure;
}

void Objects::accruePoint(int countOfCompletedRows)
{
    switch (countOfCompletedRows)
    {
        case 1:
            score += 100;
            break;

        case 2:
            score += 300;
            break;

        case 3:
            score += 700;
            break;

        case 4:
            score += 1500;
            break;

        default:
            break;
    }
}

void Objects::createCopyOfNextFigure()
{
    sf::Vector2f positionOfNext = nextFigure->getSize();
    sf::Vector2f pos(
            375 + ((240 - positionOfNext.x) / 2),
            30 + ((180 -  positionOfNext.y) / 2)
    );

    delete copyOfNextFigure;

    if (nextFigure->getName() == 'I') copyOfNextFigure = new I(pos);
    if (nextFigure->getName() == 'J') copyOfNextFigure = new J(pos);
    if (nextFigure->getName() == 'L') copyOfNextFigure = new L(pos);
    if (nextFigure->getName() == 'O') copyOfNextFigure = new O(pos);
    if (nextFigure->getName() == 'S') copyOfNextFigure = new S(pos);
    if (nextFigure->getName() == 'T') copyOfNextFigure = new T(pos);
    if (nextFigure->getName() == 'Z') copyOfNextFigure = new Z(pos);

    nextFigure->makeCopy(copyOfNextFigure);
}
