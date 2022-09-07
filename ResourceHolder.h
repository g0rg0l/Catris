#ifndef TETRIS_RESOURCEHOLDER_H
#define TETRIS_RESOURCEHOLDER_H

#include "SFML/Graphics.hpp"
#include <map>
#include <string>

// Тут пока что находится только Texture holder, однако в будущем будет и реализация Sound Holde'а
// Поэтому файл и называется "ResourceHolder"

class TextureHolder
{

private:
    std::map<std::string, sf::Texture*> resourcesMap;

public:
    /////////////////////////////////// Конструкторы и деструкторы ///////////////////////////////////
    TextureHolder() = default;
    ~TextureHolder();

    /////////////////////////////////// Получение глобального textureholder'а ///////////////////////////////////
    static TextureHolder& getInstance();

    /////////////////////////////////// Работа с TextureHolder'ом ///////////////////////////////////
    void loadFromFile(const std::string &fileName, const std::string &key); // Загрузка в TextureHolder текстуры

    sf::Texture* getResource(const std::string &key); // Получение их TextureHolder'а текстуры
};
#endif //TETRIS_RESOURCEHOLDER_H
