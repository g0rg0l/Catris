#ifndef TETRIS_S_H
#define TETRIS_S_H

#include "../Figure.h"

class S : public Figure
{

public:
    explicit S(sf::Vector2f pos = {0, 0});
};
#endif //TETRIS_S_H
