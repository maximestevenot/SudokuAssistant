/**
 * Copyright © Maxime Stevenot, Guillaume Hannes
 *
 * This file is part of Sudoku Assistant
 *
 * This software is governed by the CeCILL license under French law
 * and abiding by the rules of distribution of free software.
 */

#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (QLocale::system().language() == QLocale::French)
    {
        QTranslator * appTranslator = new QTranslator();
        bool appTranslatorLoaded = appTranslator->load("translations/SudokuAssistant_frFR.qm", ":/translations");
        if (appTranslatorLoaded)
        {
            a.installTranslator(appTranslator);
        }
    }

    SudokuAssistant::View::MainWindow w;
    w.show();

    return a.exec();
}
