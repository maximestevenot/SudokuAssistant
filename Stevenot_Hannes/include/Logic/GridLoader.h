/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 * 
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#ifndef GRIDLOADER_H
#define GRIDLOADER_H

#include "Grid.h"
#include "Controller.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

namespace SudokuAssistant {
namespace Logic {

class GridLoader
{
public:
    static Model::Grid * getNewGrid(Controller::Difficulty difficulty = static_cast<Controller::Difficulty>(0));
    static Model::Grid * getNewGridFromSave(const QString & path);

private:

    static QFile * openFile(Controller::Difficulty);
    static int getRandomLineIndex(int lineCount);
    static QStringList getLine(QTextStream & in, int index);
};

}
}
#endif
