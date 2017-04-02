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

    struct Pos {
        int x;
        int y;
    };

    struct Cell {
        QList<int> possibleValues;
        bool assigned;
        QList<Pos*> peers;
    };

private:
    Solver() {}
    const static int SIZE = 9;
    Grid * _grid;
    Cell _solvedTable[SIZE][SIZE];

    void initSolvedTable();
    void initCellTable(Cell tab[SIZE][SIZE]);
    bool solve();

    // Forward Checking
    void eliminateFC(Cell branch[SIZE][SIZE], Pos &, int);
    void assignFC(Cell branch[SIZE][SIZE], Pos &, int);

};

}

#endif // SOLVER_H
