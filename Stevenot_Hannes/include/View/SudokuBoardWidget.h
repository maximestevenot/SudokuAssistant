/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef SUDOKUBOARDWIDGET_H
#define SUDOKUBOARDWIDGET_H

#include "Controller.h"
#include "SudokuBox.h"
#include <QWidget>
#include <QPaintEvent>
#include <QGridLayout>

namespace SudokuAssistant {
namespace View {

class SudokuBox;

class SudokuBoardWidget : public QWidget
{
    Q_OBJECT

public:

    explicit SudokuBoardWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void initializeWidget(Controller * controller);
    int boxSize();

signals:
    void onBoxClicked(int, int);

public slots:
    void updateGrid();
    void updateBox(int i, int j, int value);

private slots:
    void boxesClickAction(int, int);

private:
    int _boxSize;
    QGridLayout * _layout;
    Controller * _controller;
    SudokuBox * _boxes[Grid::SIZE][Grid::SIZE];

    void deleteBoxes();
};

}
}
#endif
