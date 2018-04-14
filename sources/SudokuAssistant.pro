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
        src/View/ActiveSudokuBox.cpp \
        src/View/MainWindow.cpp \
        src/View/SudokuBoardWidget.cpp \
        src/View/SudokuBox.cpp \
    src/View/InactiveSudokuBox.cpp \
    src/View/DigitEntry.cpp \
    src/View/VictoryWindow.cpp \
    src/Model/Grid.cpp \
    src/Logic/Controller.cpp \
    src/Logic/Solver.cpp \
    src/Logic/GridLoader.cpp

HEADERS  += \
            include/View/ActiveSudokuBox.h \
            include/View/MainWindow.h \
            include/View/SudokuBoardWidget.h \
            include/View/SudokuBox.h \
    include/View/InactiveSudokuBox.h \
    include/View/DigitEntry.h \
    include/View/VictoryWindow.h \
    include/Model/Grid.h \
    include/Logic/Controller.h \
    include/Logic/GridLoader.h \
    include/Logic/Solver.h

FORMS    += ui/MainWindow.ui \
    ui/VictoryWindow.ui

MOC_DIR  = moc
OBJECTS_DIR  = obj

INCLUDEPATH +=  include \
                include/View/ \
                include/Model/ \
                include/Logic

RESOURCES += \
    resources/resources.qrc

TRANSLATIONS = resources/translations/SudokuAssistant_frFR.ts
