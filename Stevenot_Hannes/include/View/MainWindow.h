/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 * 
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controller.h"

namespace SudokuAssistant {
namespace View {

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool askSaving();

public slots:
        void onBoxUpdateRequested(int i, int j);

        void saveGame();
        void saveGameAs();
        void loadGame();

private:
    Ui::MainWindow *ui;
    Controller * _controller;
    QString _savingPath;

    void initComboBox();

private slots:
    void exitApplication();
};

}
}

#endif // MAINWINDOW_H
