#ifndef TETRIS_I_H
#define TETRIS_I_H

#include "../Figure.h"

class I : public Figure
{

public:
    explicit I(sf::Vector2f pos = {0, 0});
};
#endif //TETRIS_I_H
