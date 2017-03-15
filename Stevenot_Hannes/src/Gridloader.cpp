#include "Gridloader.h"

#include <random>
#include <chrono>
#include <QFile>
#include <QTextStream>
#include <QString>


Grid * GridLoader::getNewGrid(Controller::Difficulty difficulty)
{
    QFile * file = openFile(difficulty);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //TODO manage error properly
    }

    QTextStream in(file);
    int lineCount = in.readLine().toInt();
    int lineIndex = getRandomLineIndex(lineCount);

    QStringList line = getLine(in, lineIndex);
    file->close();

    return new Grid(line);
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
