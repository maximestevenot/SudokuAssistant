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

    connect(ui->action_Quit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(onNewGame()));
    connect(ui->action_Restart, SIGNAL(triggered(bool)), _controller, SLOT(onClearGrid()));
    connect(ui->action_Open, SIGNAL(triggered(bool)), this, SLOT(onLoadGame()));
    connect(ui->action_Save, SIGNAL(triggered(bool)), this, SLOT(onSaveGame()));
    connect(ui->action_Save_As, SIGNAL(triggered(bool)), this, SLOT(onSaveGameAs()));
    connect(ui->action_Check_grid, SIGNAL(triggered(bool)), this, SLOT(onCheckGrid()));

    connect(ui->_sudokuBoard, SIGNAL(boxClicked(int,int)), this, SLOT(onBoxUpdateRequested(int,int)));

    connect(ui->newGameButton, SIGNAL(released()), this, SLOT(onNewGame()));
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
    userInput.move(QCursor::pos());
    userInput.exec();
}

void MainWindow::onSaveGame()
{
    if (_savingPath.isEmpty())
    {
        onSaveGameAs();
    }
    else
    {
        _controller->saveGame(_savingPath);
    }
}

void MainWindow::onSaveGameAs()
{
    _savingPath = QFileDialog::getSaveFileName(this, QString(), QString(),
                                               tr("Sudoku (*.sds);;All Files(*)"));
    _controller->saveGame(_savingPath);
}

void MainWindow::onLoadGame()
{
    if (_controller->userShouldSave() && !askSaving())
    {
        return;
    }

    QString path = QFileDialog::getOpenFileName(this, QString(), QString(),
                                                tr("Sudoku (*.sds);;All Files(*)"));
    _controller->loadGame(path);
    _savingPath = path;
}

void MainWindow::onNewGame()
{
    if (_controller->userShouldSave() && !askSaving())
    {
        return;
    }
    _controller->onNewGrid();
}

void MainWindow::onCheckGrid()
{
    qDebug() << _controller->checkGrid();
}

void MainWindow::closeEvent(QCloseEvent * evt)
{
    if (_controller->userShouldSave() && !askSaving())
    {
        evt->ignore();
        return;
    }
    evt->accept();
}

bool MainWindow::askSaving()
{
    QMessageBox msgBox(this);
    msgBox.setText(tr("The document has been modified."));
    msgBox.setInformativeText(tr("Do you want to save your changes?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    int choice = msgBox.exec();
    bool ret = true;

    switch (choice)
    {
    case QMessageBox::Save :
        onSaveGame();
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
