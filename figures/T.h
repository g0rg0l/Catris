#ifndef TETRIS_T_H
#define TETRIS_T_H

#include "../Figure.h"

class T : public Figure
{

public:
    explicit T(sf::Vector2f pos = {0, 0});
};
#endif //TETRIS_T_H
