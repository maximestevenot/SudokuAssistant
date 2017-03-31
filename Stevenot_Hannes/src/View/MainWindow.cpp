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
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

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
    connect(ui->action_New, SIGNAL(triggered(bool)), _controller, SLOT(onNewGrid()));
    connect(ui->action_Restart, SIGNAL(triggered(bool)), _controller, SLOT(onClearGrid()));
    connect(ui->action_Open, SIGNAL(triggered(bool)), this, SLOT(loadGame()));
    connect(ui->action_Save, SIGNAL(triggered(bool)), this, SLOT(saveGame()));
    connect(ui->action_Save_As, SIGNAL(triggered(bool)), this, SLOT(saveGameAs()));

    connect(ui->_sudokuBoard, SIGNAL(boxClicked(int,int)), this, SLOT(onBoxUpdateRequested(int,int)));

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
    View::DigitEntry userInput(i, j, _controller);
    connect(&userInput, SIGNAL(boxUpdated(int,int,int)), _controller, SLOT(onGridUpdate(int,int,int)));
    userInput.setModal(true);
    QPoint popupPos(QCursor::pos().x() + userInput.width() / 10, QCursor::pos().y() + userInput.height() / 10);
    userInput.move(this->mapFromGlobal(popupPos));
    userInput.exec();
}

void MainWindow::saveGame()
{
    if (_savingPath.isEmpty())
    {
        saveGameAs();
    }
    else
    {
        _controller->saveGame(_savingPath);
    }
}

void MainWindow::saveGameAs()
{
    _savingPath = QFileDialog::getSaveFileName(this, QString(), QString(),
                                               tr("Sudoku (*.bin);;All Files(*)"));
    _controller->saveGame(_savingPath);
}

void MainWindow::loadGame()
{
    QString path = QFileDialog::getOpenFileName(this, QString(), QString(),
                                                tr("Sudoku (*.bin);;All Files(*)"));
    _controller->loadGame(path);
}

void MainWindow::exitApplication()
{
    QApplication::quit();
}

bool MainWindow::askSaving()
{
    QMessageBox msgBox(this);
    msgBox.setText(tr("The document has been modified."));
    msgBox.setInformativeText(tr("Do you want to save your changes?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Ignore | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    int choice = msgBox.exec();
    bool ret = true;

    switch (choice)
    {
    case QMessageBox::Save :
        saveGame();
        break;
    case QMessageBox::Cancel :
        ret = false;
        break;
    default:
        break;
    }

    return ret;
}

}
}
