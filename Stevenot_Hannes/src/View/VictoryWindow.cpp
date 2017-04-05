/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "VictoryWindow.h"
#include "ui_VictoryWindow.h"

namespace SudokuAssistant {
namespace View {

VictoryWindow::VictoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VictoryWindow)
{
    ui->setupUi(this);
    this->setModal(true);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

VictoryWindow::~VictoryWindow()
{
    delete ui;
}

}
}
