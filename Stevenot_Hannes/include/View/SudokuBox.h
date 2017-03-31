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

    static const QColor & defaultBackgroundColor();
    static const QColor & highlightedBackgroundColor();
    const QColor & backgroundColor() const;
    void setBackgroundColor(const QColor &);

public:
    int iIndex() const;
    int jIndex() const;
    int value() const;
    SudokuBoardWidget* parentBoard() const;

public slots:
    virtual void updateValue(int value);
    virtual void highlight() = 0;
    virtual void markAsWrong() = 0;
    virtual void restoreDefaultStyle() = 0;

signals:
    void onMouseClicked(int, int);

private:
    int _i;
    int _j;
    int _value;
    SudokuBoardWidget * _boardWidget;

    static const QColor DefaultBackgroundColor;
    static const QColor HighlightedBackgroundColor;
    QColor _backgroundColor;
};

}
}
#endif
