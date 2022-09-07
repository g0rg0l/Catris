#ifndef TETRIS_O_H
#define TETRIS_O_H

#include "../Figure.h"

class O : public Figure
{

public:
    explicit O(sf::Vector2f pos = {0, 0});
};
#endif //TETRIS_O_H
