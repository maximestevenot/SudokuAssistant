#ifndef GRIDLOADER_H
#define GRIDLOADER_H

#include "Grid.h"
#include "Controller.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

class GridLoader
{
public:
    static Grid * getNewGrid(Controller::Difficulty difficulty = static_cast<Controller::Difficulty>(0));

private:
    static QFile * openFile(Controller::Difficulty);
    static int getRandomLineIndex(int lineCount);
    static QStringList getLine(QTextStream & in, int index);
};

#endif
