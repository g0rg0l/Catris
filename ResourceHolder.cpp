#include "ResourceHolder.h"


/////////////////////////////////// Конструкторы и деконструкторы ///////////////////////////////////
TextureHolder::~TextureHolder()
{
    for (auto &resource : resourcesMap)
    {
        delete resource.second;
    }
}

/////////////////////////////////// Получение глобального textureholder'а ///////////////////////////////////
TextureHolder& TextureHolder::getInstance()
{
    static TextureHolder textureHolder;

    return textureHolder;
}

/////////////////////////////////// Работа с TextureHolder'ом ///////////////////////////////////
void TextureHolder::loadFromFile(const std::string &fileName, const std::string &key) // Загрузка в TextureHolder текстуры
{
    sf::Texture* &resource = resourcesMap[key];

    if (resource == nullptr)
    {
        resource = new sf::Texture;

        if (!resource->loadFromFile(fileName))
        {
            delete resource;
        }
    }
}

sf::Texture* TextureHolder::getResource(const std::string &key) // Получение их TextureHolder'а текстуры
{
    auto pairResourceIterator = resourcesMap.find(key);

    if (pairResourceIterator == resourcesMap.end())
    {
        return nullptr;
    }

    return pairResourceIterator->second;
}