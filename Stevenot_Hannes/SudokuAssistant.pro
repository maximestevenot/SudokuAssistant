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
        src/MainWindow.cpp \
        src/Grid.cpp \
        src/Controller.cpp \
    src/Gridloader.cpp \
    src/SudokuBoardWidget.cpp \
    src/SudokuBox.cpp \
    src/ActiveSudokuBox.cpp

HEADERS  += include/MainWindow.h \
            include/Controller.h \
            include/Grid.h \
    include/Gridloader.h \
    include/SudokuBoardWidget.h \
    include/SudokuBox.h \
    include/ActiveSudokuBox.h

FORMS    += ui/MainWindow.ui

MOC_DIR  = moc
OBJECTS_DIR  = obj

INCLUDEPATH += ./include

RESOURCES += \
    resources/resources.qrc
