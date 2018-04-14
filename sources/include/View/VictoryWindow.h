/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
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
