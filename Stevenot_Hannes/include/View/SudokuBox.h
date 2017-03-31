/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

#include "SudokuBoardWidget.h"
#include <QWidget>
#include <QColor>

namespace SudokuAssistant {
namespace View {

class SudokuBoardWidget;

class SudokuBox : public QWidget
{
    Q_OBJECT

protected:
    explicit SudokuBox(int i, int j, int value = 0, QWidget * parent = 0);
    virtual void paintEvent(QPaintEvent *);

public:
    int iIndex();
    int jIndex();

    QColor defaultBackgroundColor();
    QColor tipsBackgroundColor();
    const QColor & backgroundColor();
    void setBackgroundColor(const QColor &);

    int value();
    SudokuBoardWidget* parentBoard();

public slots:
    virtual void updateValue(int value);

signals:
    void onMouseClicked(int, int);

private:
    int _i;
    int _j;
    int _value;
    SudokuBoardWidget * _boardWidget;
    QColor _backgroundColor;
};

}
}
#endif
