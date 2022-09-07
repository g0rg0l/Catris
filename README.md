# Catris - Tetris in the style of Hello Kitty

Данный проект представляет собой ремейк знаменитейшей игры, в которую, наверное, играл каждый - **Tetris** на языке C++.

В качестве оформления была выбрана чуть менее популярная игра из серии **Hello Kitty**.

![preview1](https://github.com/g0rg0l/Catris/blob/master/github_src/preview1.jpg?raw=true)
![preview2](https://github.com/g0rg0l/Catris/blob/master/github_src/preview2.jpg?raw=true)

## Инструментарий

Для реализации была выбрана библиотека для разработки игр на языке C++, основанная на OpenGL - **SFML**.

## Установка

Чтобы запустить игру, необходимо установить все приложенные файлы, кроме папки `github_src`, а также подключить саму библиотеку следующими командами в вашем Cmake файле:
```
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR YOUR_PATH_TO_THE_SFML_LIBRARY)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(YOUR_PATH_TO_THE_INCLUDE_FOLDER_OF_SFML_LIBRARY)
target_link_libraries(NAME_OF_YOUR_PROJECT sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
```

## Управление

Всего есть 3 кнопки управления:
  - **PageDown** - сдвиг фигуры вниз
  - **PageRight** - сдвиг фигуры вправо
  - **PageLeft** - сдвиг фигуры влево

## Демонстрация

Ниже приведён краткий обзор гемплея.

![preview3](https://github.com/g0rg0l/Catris/blob/master/github_src/video.gif?raw=true)


