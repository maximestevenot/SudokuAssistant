#-------------------------------------------------
#
# Project created by QtCreator 2017-02-09T11:01:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculatrice
TEMPLATE = app
CONFIG  += warn_on
CONFIG  += c++11
QT += core gui widgets

INCLUDEPATH += ./include
DEPENDPATH += ./include

SOURCES += src/Controller.cpp \
        src/main.cpp \
        src/mainwindow.cpp

HEADERS  += include/Controller.h \
        include/mainwindow.h
