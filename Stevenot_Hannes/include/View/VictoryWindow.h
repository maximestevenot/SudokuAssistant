/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef VICTORYWINDOW_H
#define VICTORYWINDOW_H

#include <QDialog>

namespace SudokuAssistant {
namespace View {

namespace Ui {
class VictoryWindow;
}

class VictoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VictoryWindow(QWidget *parent = 0);
    ~VictoryWindow();

private:
    Ui::VictoryWindow * ui;
};

}
}

#endif
