/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 * 
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef ACTIVESUDOKUBOX_H
#define ACTIVESUDOKUBOX_H

#include "SudokuBox.h"

namespace SudokuAssistant {
namespace View {

class ActiveSudokuBox : public SudokuBox
{
    Q_OBJECT

public:
    explicit ActiveSudokuBox(int i, int j, int value = 0, QWidget * parent = 0);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

public slots:
    void updateValue(int value);
};

}
}

#endif
