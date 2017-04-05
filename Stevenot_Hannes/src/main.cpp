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
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (QLocale::system().language() == QLocale::French)
    {
        QTranslator * appTranslator = new QTranslator();
        appTranslator->load("translations/SudokuAssistant_frFR.qm", ":/translations");
        a.installTranslator(appTranslator);
    }

    SudokuAssistant::View::MainWindow w;
    w.show();

    return a.exec();
}
