#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T16:04:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuAssistant
TEMPLATE = app

CONFIG  += c++11

SOURCES += src/main.cpp\
        src/Grid.cpp \
        src/Controller.cpp \
        src/Gridloader.cpp \
        src/View/ActiveSudokuBox.cpp \
        src/View/MainWindow.cpp \
        src/View/SudokuBoardWidget.cpp \
        src/View/SudokuBox.cpp \
    src/View/InactiveSudokuBox.cpp \
    src/View/DigitEntry.cpp \
    src/Solver.cpp

HEADERS  += \
            include/Controller.h \
            include/Grid.h \
            include/Gridloader.h \
            include/View/ActiveSudokuBox.h \
            include/View/MainWindow.h \
            include/View/SudokuBoardWidget.h \
            include/View/SudokuBox.h \
    include/View/InactiveSudokuBox.h \
    include/View/DigitEntry.h \
    include/Solver.h

FORMS    += ui/MainWindow.ui

MOC_DIR  = moc
OBJECTS_DIR  = obj

INCLUDEPATH +=  include \
                include/View/

RESOURCES += \
    resources/resources.qrc

TRANSLATIONS = SudokuAssistant_frFR.ts
