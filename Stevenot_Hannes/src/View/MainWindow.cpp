/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DigitEntry.h"
#include <QString>
#include <QPoint>

namespace SudokuAssistant {
namespace View {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));

    initComboBox();

    _controller = new Controller();
    _controller->setDifficulty();

    ui->_sudokuBoard->initializeWidget(_controller);

    connect(ui->action_Quit, SIGNAL(triggered(bool)), this, SLOT(exitApplication()));

    connect(ui->_sudokuBoard, SIGNAL(boxClicked(int,int)), this, SLOT(onBoxUpdateRequested(int,int)));
    connect(ui->action_New, SIGNAL(triggered(bool)), _controller, SLOT(onNewGrid()));
    connect(ui->newGameButton, SIGNAL(released()), _controller, SLOT(onNewGrid()));
    connect(ui->difficultyComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), _controller, [=](int i){ _controller->setDifficulty(static_cast<Controller::Difficulty>(i)); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initComboBox()
{
    for (int diff = 0; diff < Controller::Difficulty_Count; diff++)
    {
        ui->difficultyComboBox->addItem(Controller::Difficulty_Level[diff], static_cast<Controller::Difficulty>(diff));
    }
}

void MainWindow::onBoxUpdateRequested(int i, int j)
{
    View::DigitEntry userInput(i, j);
    connect(&userInput, SIGNAL(boxUpdated(int,int,int)), _controller, SLOT(onGridUpdate(int,int,int)));
    userInput.setModal(true);
    QPoint popupPos(QCursor::pos().x() + userInput.width() / 10, QCursor::pos().y() + userInput.height() / 10);
    userInput.move(this->mapFromGlobal(popupPos));
    userInput.exec();
}

void MainWindow::exitApplication()
{
    QApplication::quit();
}

}
}
