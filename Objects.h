#ifndef TETRIS_OBJECTS_H
#define TETRIS_OBJECTS_H

#include <vector>

#include "Figure.h"
#include "figures/J.h"
#include "figures/L.h"
#include "figures/I.h"
#include "figures/O.h"
#include "figures/Z.h"
#include "figures/T.h"
#include "figures/S.h"

class Objects
{

public:
    Objects();
    ~Objects();

public:
    void updateFigures(float &spentTime);
    int checkForCompletedRows();
    void deleteRow(int i);
    void reshapeRows(int index);
    void checkForLose();

    Figure* generateNewFigure();
    void createCopyOfNextFigure();

    void accruePoint(int countOfCompletedRows);

public:
    Figure* fallingFigure = nullptr; // Падающая фигура
    Figure* nextFigure = nullptr; // Следующая фигура
    Figure* copyOfNextFigure = nullptr;
    std::vector<Square> fallenSquares; // Вектор всех Square упавших фигур

    unsigned int** table; // Таблица позиций тетриса "0" - свободный квадрат, "1" - занятый

    int score = 0;
    int lineCount = 0;
    bool lost = false;
};


#endif //TETRIS_OBJECTS_H
