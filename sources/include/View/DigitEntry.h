/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
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
    explicit DigitEntry(int iBox, int jBox, Logic::Controller * controller, QWidget *parent = 0);

signals:
    void boxUpdated(int, int, int);

public slots:
    void onDigitButtonClicked(int);
    void onClearButtonClicked();

private:
    int _i;
    int _j;
    Logic::Controller * _controller;

    void initButtons();
};

}
}
#endif
