/**
 * @file   main.cpp
 * @author Guillaume Hannes
 * @author Maxime Stevenot
 */

#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (QLocale::system().language() == QLocale::French)
    {
        QTranslator * qtTranslator = new QTranslator();
        qtTranslator->load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        app.installTranslator(qtTranslator);

        QTranslator * appTranslator = new QTranslator();
        appTranslator->load("billwidget_fr.qm", ":/translations/ts");
        app.installTranslator(appTranslator);
    }

    MainWindow w;
    w.show();

    return app.exec();
}
