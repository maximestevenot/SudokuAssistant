/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
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
    connect(ui->pushButton, &QAbstractButton::clicked, this, &QWidget::close);
}

VictoryWindow::~VictoryWindow()
{
    delete ui;
}

}
}
