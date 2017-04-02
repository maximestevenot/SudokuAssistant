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
#include <QVector>

namespace SudokuAssistant {

class Solver
{

public:
    Solver();
    Solver(Grid *);
    ~Solver();
    bool CheckGrid();

private:
    const static int SIZE = 9;
    Grid * _grid;
    int _numOfBacktracking;

    struct Pos {
        int x;
        int y;
    };

    struct Cell {
        Cell()
        {
            possibleValues = {1,2,3,4,5,6,7,8,9};
            assigned = false;
        }

        QList<int> possibleValues;
        bool assigned;
        QList<Pos> peers;
        QList<Pos> units[3];
    };
    QVector<Cell> * _solvedTable;
    static int index(int, int);

    void initCellTable(QVector<Cell> *);
    bool solve();

    // Forward Checking
    QVector<Cell> * eliminateFC(QVector<Cell> *, Pos &, int);
    QVector<Cell> * assignFC(QVector<Cell> *, Pos &, int);

    // Arc consistency
    QVector<Cell> * assignAC(QVector<Cell> *, Pos &, int);
    QVector<Cell> * eliminateAC(QVector<Cell> *, Pos &, int);

    QVector<Cell> * backtrackingSearch(QVector<Cell> *);

};

}

#endif // SOLVER_H
