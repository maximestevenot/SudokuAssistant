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
    src/Grid.cpp

HEADERS  += include/MainWindow.h \
    include/Grid.h

FORMS    += ui/MainWindow.ui

MOC_DIR  = moc
OBJECTS_DIR  = obj

INCLUDEPATH += ./include
