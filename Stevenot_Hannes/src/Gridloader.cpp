/*
 * Copyright (C) ENSICAEN 2016-2017
 * Authors : Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */
#include "Gridloader.h"
#include <random>
#include <chrono>
#include <QFile>
#include <QTextStream>
#include <QString>

namespace SudokuAssistant {

Grid * GridLoader::getNewGrid(Controller::Difficulty difficulty)
{
    QFile * file = openFile(difficulty);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return nullptr;
    }

    QTextStream in(file);
    int lineCount = in.readLine().toInt();
    int lineIndex = getRandomLineIndex(lineCount);

    QStringList line = getLine(in, lineIndex);
    file->close();

    return new Grid(line);
}

Grid * GridLoader::getNewGridFromSave(const QString & path)
{
    Grid * grid = new Grid();

    if (path.isEmpty())
    {
        return nullptr;
    }

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return nullptr;
    }

    QDataStream in(&file);
    in >> (*grid);
    file.close();

    return grid;
}

QFile * GridLoader::openFile(Controller::Difficulty difficulty)
{
    QString fileName;

    switch (difficulty)
    {
    case Controller::Difficulty_Easy:
        fileName = ":/grids/Easy";
        break;
    case Controller::Difficulty_Medium:
        fileName = ":/grids/Medium";
        break;
    case Controller::Difficulty_Hard:
        fileName = ":/grids/Hard";
        break;
    case Controller::Difficulty_Insane:
        fileName = ":/grids/Insane";
        break;
    default:
        // TODO make random grid
        fileName = ":/grids/Medium";
        break;
    }

    return new QFile(fileName);
}

int GridLoader::getRandomLineIndex(int lineCount)
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1, lineCount);
    int i = distribution(generator);
    return i;
}

QStringList GridLoader::getLine(QTextStream & in, int index)
{
    int currentLine = 1;
    QString line;

    do
    {
        line = in.readLine();
        currentLine++;
    } while (!in.atEnd() && currentLine < index);

    return line.split(" ");
}

}
