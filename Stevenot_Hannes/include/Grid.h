/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 * 
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef GRID_H
#define GRID_H

#include <QList>
#include <QStringList>

namespace SudokuAssistant {

class Grid
{

public:

    const static int SIZE = 9;

    Grid();
    Grid(QStringList);

    void load(QList<int>);
    void load(QStringList);

    void clear();

    void setValue(int i, int j, int value);
    int getValue(int i, int j);
    QList<int> getLine(int i);
    QList<int> getColumn(int j);
    bool isReadOnly(int i, int j);

private:

    struct Cell {
        int value;
        bool readOnly;
    };

    Cell _tab[SIZE][SIZE];

};

}

#endif
