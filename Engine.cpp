#include "Engine.h"

Engine::Engine()
{
    srand(GetTickCount64());
    window.create(sf::VideoMode(660, 660), "Tetris");

    titleFont.loadFromFile("../src/haFont.ttf");

    loadDesignElements();
}

void Engine::runEngine()
{
    while(window.isOpen())
    {
        update();
        pollEvents();
        draw();
    }
}

void Engine::update()
{
    spentTime += clock.getElapsedTime().asSeconds();
    keyboardTime += clock.getElapsedTime().asSeconds();

    if (!objects.lost)
    {
        if (spentTime > 1)
        {
            spentTime = 0;
            objects.updateFigures(spentTime);
        }
        if (keyboardTime > 0.15)
        {
            keyboardTime = 0;
            if (!objects.lost) checkForMove();
        }
    }

    clock.restart();
}

void Engine::pollEvents()
{
    sf::Event event{};

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }
    }
}

void Engine::draw()
{
    window.clear();

    for (auto& element : designElements)
    {
        window.draw(element);
    }

    if (!objects.lost) window.draw(*(objects.fallingFigure));

    for (auto& square : objects.fallenSquares)
    {
        window.draw(square);
    }

    for (auto& line : grid)
    {
        window.draw(line);
    }

    for (auto& word : text)
    {
        window.draw(word);
    }
    scoreText.setString(std::to_string(objects.score));
    window.draw(scoreText);
    lineCountText.setString(std::to_string(objects.lineCount));
    window.draw(lineCountText);

    window.draw(*(objects.copyOfNextFigure));

    window.display();
}

void Engine::loadDesignElements()
{
    /* Загрузка в ResourceHolder изображений */
    TextureHolder& textureHolder = TextureHolder::getInstance();
    textureHolder.loadFromFile("../src/background.png", "tetrisBackground");
    textureHolder.loadFromFile("../src/helloKitty.png", "helloKitty");

    /* Задний фон */
    sf::RectangleShape background(sf::Vector2f(660, 660));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(255, 173, 216));
    designElements.push_back(background);

    /* Поле Тетриса */
    sf::RectangleShape tetrisArea(sf::Vector2f(300, 600));
    tetrisArea.setPosition(30, 30);
    sf::Texture* tetrisAreaBackground = textureHolder.getResource("tetrisBackground");
    tetrisArea.setTexture(tetrisAreaBackground);
    designElements.push_back(tetrisArea);

    /* Четыре линии рамки вокруг поле Тетриса */
    sf::RectangleShape tetrisBorderUp(sf::Vector2f(330, 15));
    tetrisBorderUp.setPosition(sf::Vector2f(15, 15));
    tetrisBorderUp.setFillColor(sf::Color(255, 92, 175));
    designElements.push_back(tetrisBorderUp);

    sf::RectangleShape tetrisBorderLeft(sf::Vector2f(15, 630));
    tetrisBorderLeft.setPosition(sf::Vector2f(15, 15));
    tetrisBorderLeft.setFillColor(sf::Color(255, 92, 175));
    designElements.push_back(tetrisBorderLeft);

    sf::RectangleShape tetrisBorderDown(sf::Vector2f(330, 15));
    tetrisBorderDown.setPosition(sf::Vector2f(15, 630));
    tetrisBorderDown.setFillColor(sf::Color(255, 92, 175));
    designElements.push_back(tetrisBorderDown);

    sf::RectangleShape tetrisBorderRight(sf::Vector2f(15, 630));
    tetrisBorderRight.setPosition(sf::Vector2f(330, 15));
    tetrisBorderRight.setFillColor(sf::Color(255, 92, 175));
    designElements.push_back(tetrisBorderRight);

    /* Сетка поля Тетриса */
    for (int i = -1; i < 20; ++i) // Вертикальные полосы
    {
        sf::RectangleShape line(sf::Vector2f(300, 2));
        line.setPosition(
                30,
                30 + (i + 1) * 30 - 1
                );
        line.setFillColor(sf::Color(180, 180, 180));
        grid.push_back(line);
    }

    for (int i = -1; i < 10; ++i) // Горизонтальные полосы
    {
        sf::RectangleShape line(sf::Vector2f(2, 600));
        line.setPosition(
                30 + (i + 1) * 30 - 1,
                30
        );
        line.setFillColor(sf::Color(180, 180, 180));
        grid.push_back(line);
    }

    /* Окно "next figure" */
    sf::RectangleShape nextFigureArea(sf::Vector2f(240, 180));
    nextFigureArea.setPosition(375, 30);
    nextFigureArea.setFillColor(sf::Color(254, 215, 233));
    designElements.push_back(nextFigureArea);

    /* Четыре линии вокруг окна next figure */
    sf::RectangleShape nextFigureAreaBorderUp(sf::Vector2f(270, 15));
    nextFigureAreaBorderUp.setPosition(sf::Vector2f(360, 15));
    nextFigureAreaBorderUp.setFillColor(sf::Color(255, 92, 175));
    designElements.push_back(nextFigureAreaBorderUp);

    sf::RectangleShape nextFigureAreaBorderLeft(sf::Vector2f(15, 210));
    nextFigureAreaBorderLeft.setPosition(sf::Vector2f(360, 15));
    nextFigureAreaBorderLeft.setFillColor(sf::Color(255, 92, 175));
    designElements.push_back(nextFigureAreaBorderLeft);

    sf::RectangleShape nextFigureAreaBorderDown(sf::Vector2f(270, 15));
    nextFigureAreaBorderDown.setPosition(sf::Vector2f(360, 210));
    nextFigureAreaBorderDown.setFillColor(sf::Color(255, 92, 175));
    designElements.push_back(nextFigureAreaBorderDown);

    sf::RectangleShape nextFigureAreaBorderRight(sf::Vector2f(15, 210));
    nextFigureAreaBorderRight.setPosition(sf::Vector2f(615, 15));
    nextFigureAreaBorderRight.setFillColor(sf::Color(255, 92, 175));
    designElements.push_back(nextFigureAreaBorderRight);

    /* Иконка Hello kitty */
    sf::RectangleShape helloKitty(sf::Vector2f(72, 72));
    helloKitty.setPosition(sf::Vector2f(573, 573));
    sf::Texture* helloKittyTexture = textureHolder.getResource("helloKitty");
    helloKitty.setTexture(helloKittyTexture);
    designElements.push_back(helloKitty);

    /* Текст, выводящий сумму очков и количество закрытых линий */
    sf::Text scoreTitle;
    scoreTitle.setFont(titleFont);
    scoreTitle.setString("Score");
    scoreTitle.setCharacterSize(40);
    scoreTitle.setPosition(365, 240);
    scoreTitle.setFillColor(sf::Color::Black);
    text.push_back(scoreTitle);

    scoreText.setFont(titleFont);
    scoreText.setCharacterSize(40);
    scoreText.setPosition(365, 300);
    scoreText.setFillColor(sf::Color(178, 50, 109));


    sf::Text rowsCountTitle;
    rowsCountTitle.setFont(titleFont);
    rowsCountTitle.setString("Lines");
    rowsCountTitle.setCharacterSize(40);
    rowsCountTitle.setPosition(365, 380);
    rowsCountTitle.setFillColor(sf::Color::Black);
    text.push_back(rowsCountTitle);

    lineCountText.setFont(titleFont);
    lineCountText.setCharacterSize(40);
    lineCountText.setPosition(365, 440);
    lineCountText.setFillColor(sf::Color(178, 50, 109));
}

void Engine::checkForMove()
{
    /* Movement */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        objects.fallingFigure->move("left", objects.table);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        objects.fallingFigure->move("right", objects.table);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (objects.fallingFigure->canWeMove("down", objects.table))
        {
            objects.fallingFigure->isMovingDown = true;
            objects.fallingFigure->move(sf::Vector2f(0, objects.fallingFigure->figurePartsSize));
        }
    }
    else if (objects.fallingFigure->isMovingDown) // Если фигура перестала двигаться игроком
    {
        objects.fallingFigure->isMovingDown = false;
        spentTime = 0.4;
    }
}
