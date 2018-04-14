/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
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
