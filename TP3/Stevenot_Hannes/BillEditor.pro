#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T15:46:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BillEditor
TEMPLATE = app

CONFIG  += c++11

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/InvoiceModel.cpp \
    src/billwidget.cpp

HEADERS  += include/mainwindow.h \
    include/InvoiceModel.h \
    include/billwidget.h

FORMS    += ui/mainwindow.ui

MOC_DIR  = moc
OBJECTS_DIR  = obj

INCLUDEPATH += ./include

RESOURCES += resource/resources.qrc

TRANSLATIONS += resource/ts/billwidget_fr.ts

DISTFILES += resource/ts/billwidget_fr.ts
