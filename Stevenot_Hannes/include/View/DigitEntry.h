/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef DIGITENTRY_H
#define DIGITENTRY_H

#include <QDialog>
#include <QList>
#include "Controller.h"

namespace SudokuAssistant {
namespace View {

class DigitEntry : public QDialog
{
    Q_OBJECT

public:
    explicit DigitEntry(int iBox, int jBox, Controller * controller, QWidget *parent = 0);

signals:
    void boxUpdated(int, int, int);

public slots:
    void onDigitButtonClicked(int);
    void onClearButtonClicked();

private:
    int _i;
    int _j;
    Controller * _controller;

    void initButtons();
};

}
}
#endif
