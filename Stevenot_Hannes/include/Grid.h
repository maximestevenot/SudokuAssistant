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

#include <QObject>
#include <QList>
#include <QStringList>
#include <QDataStream>

namespace SudokuAssistant {

class Grid : QObject
{
    Q_OBJECT

    friend QDataStream & operator<<(QDataStream & out, const Grid &);
    friend QDataStream & operator>>(QDataStream & in, Grid &);

public:
    const static int SIZE = 9;

    Grid();
    Grid(QStringList);

    int getValue(int i, int j);
    QList<int> getLine(int i);
    QList<int> getColumn(int j);
    bool isReadOnly(int i, int j);

signals:
    void onValueChanged(int i, int j, int value);

public slots:
    void setValue(int i, int j, int value);
    void load(QStringList);
    void clear();

private:
    struct Cell {
        int value;
        bool readOnly;
    };

    Cell _tab[SIZE][SIZE];

};

QDataStream & operator<<(QDataStream & out, const Grid &);
QDataStream & operator>>(QDataStream & in, Grid &);

}

#endif
