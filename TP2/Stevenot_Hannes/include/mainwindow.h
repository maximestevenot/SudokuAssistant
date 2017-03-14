#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QString>

#include "Controller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void exitApplication();
    void showAboutDialog();
    void onPadClicked(int);
    void baseChanged(int);
    void setDisplaySuffix(bool);

private:

    void initMenuBar();
    void initMainLayout();

    void updateDigitField();
    QString getSuffix();

    QGridLayout * constructPad();

    QPushButton * _buttonArray[Controller::Button_Count];
    QLineEdit * _digitField;
    Controller * _controller;
    bool _displaySuffix;
};

#endif
