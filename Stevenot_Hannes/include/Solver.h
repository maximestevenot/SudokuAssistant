/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "Grid.h"
#include <QList>

namespace SudokuAssistant {

class Solver
{

public:
    Solver(Grid *);
    static bool CheckGrid(Grid *);
    void GetHint();

private:
    Solver() {}
    const static int SIZE = 9;
    Grid * _grid;

    struct Cell {
        QList<int> possibleValues;
        bool solved;
        int answer;
    };
    Cell _solvedTable[SIZE][SIZE];

    void initSolvedTable();
    bool solve();

};

}

#endif // SOLVER_H
