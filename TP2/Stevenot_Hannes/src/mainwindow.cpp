#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QAction>
#include <QButtonGroup>
#include <QLayout>
#include <QComboBox>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _controller = new Controller;

    setCentralWidget(new QWidget(this));
    setWindowTitle("Calculatrice");

    initMenuBar();
    initMainLayout();

    updateDigitField();
}

MainWindow::~MainWindow()
{
    delete _controller;
}


void MainWindow::exitApplication()
{
    close();
}

void MainWindow::showAboutDialog()
{
    QMessageBox::about(this,
                       "A propos",
                       "Calculatrice\n(c) 2017 Sebastien Fourey");
}

void MainWindow::updateDigitField()
{
    QString display = _controller->getText();

    if (_displaySuffix)
    {
        display += getSuffix();
    }

    _digitField->setText(display);
}

void MainWindow::onPadClicked(int id)
{
    if (_controller->command((Controller::ButtonID) id))
    {
        updateDigitField();
    }
}

void MainWindow::setDisplaySuffix(bool value)
{
    _displaySuffix = value;
    updateDigitField();
}

void MainWindow::baseChanged(int index)
{
    switch (index)
    {
    case 0:

        for (int i = Controller::Button_2; i <= Controller::Button_Dot; i++)
        {
            _buttonArray[i]->setEnabled(false);
        }

        _controller->setBase(Controller::Bin);
        break;

    case 1:

        for (int i = Controller::Button_A; i <= Controller::Button_F; i++)
        {
            _buttonArray[i]->setEnabled(false);
        }

        for (int i = Controller::Button_2; i <= Controller::Button_9; i++)
        {
            _buttonArray[i]->setEnabled(true);
        }

        _buttonArray[Controller::Button_Dot]->setEnabled(true);

        _controller->setBase(Controller::Dec);
        break;

    case 2:

        for (int i = Controller::Button_2; i <= Controller::Button_F; i++)
        {
            _buttonArray[i]->setEnabled(true);
        }
        _buttonArray[Controller::Button_Dot]->setEnabled(false);

        _controller->setBase(Controller::Hex);
        break;
    }

    updateDigitField();
}

QString MainWindow::getSuffix()
{
    QString suffix;

    switch (_controller->base())
    {
    case Controller::Bin :
        suffix = "b";
        break;
    case Controller::Hex :
        suffix = "h";
        break;
    default:
        suffix = "";
        break;
    }
    return suffix;
}

void MainWindow::initMenuBar()
{
    QMenu * fileMenu = new QMenu("&Fichier", menuBar());
    QAction * exitAction = new QAction("&Quitter", fileMenu);
    fileMenu->addAction(exitAction);
    menuBar()->addMenu(fileMenu);

    QMenu * optionsMenu = new QMenu("&Options", menuBar());
    QAction * displaySuffixAction = new QAction("Afficher Suffixe", optionsMenu);
    displaySuffixAction->setCheckable(true);
    optionsMenu->addAction(displaySuffixAction);
    menuBar()->addMenu(optionsMenu);
    _displaySuffix = false;

    QMenu * helpMenu = new QMenu("&Aide", menuBar());
    QAction * aboutAction = new QAction("A &propos...", fileMenu);
    helpMenu->addAction(aboutAction);
    menuBar()->addMenu(helpMenu);

    connect(exitAction,SIGNAL(triggered()), this, SLOT(exitApplication()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
    connect(displaySuffixAction, SIGNAL(toggled(bool)), this, SLOT(setDisplaySuffix(bool)));
}

void MainWindow::initMainLayout()
{
    QVBoxLayout * mainLayout = new QVBoxLayout(centralWidget());

    QPushButton * exitButton = new QPushButton("Quitter",centralWidget());
    _digitField = new QLineEdit(centralWidget());
    _digitField->setReadOnly(true);
    _digitField->setAlignment(Qt::AlignRight);

    mainLayout->addWidget(new QLabel("Calculatrice", centralWidget()));
    mainLayout->addWidget(_digitField);
    mainLayout->addLayout(constructPad());
    mainLayout->addWidget(exitButton);

    connect(exitButton,SIGNAL(clicked()), this, SLOT(exitApplication()));
}

QGridLayout* MainWindow::constructPad()
{
    const QString textBox = "0123456789ABCDEF.+-/*=C";

    const int padOrder[] = {Controller::Button_A, Controller::Button_B, Controller::Button_C, Controller::Button_D, \
                            Controller::Button_7, Controller::Button_8, Controller::Button_9, Controller::Button_Plus, \
                            Controller::Button_4, Controller::Button_5, Controller::Button_6, Controller::Button_Minus, \
                            Controller::Button_1, Controller::Button_2, Controller::Button_3, Controller::Button_Divide, \
                            Controller::Button_0, Controller::Button_Dot, Controller::Button_Equal, Controller::Button_Multiply};

    const char * shortcuts[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", \
                                ".", "+", "-", "/", "*", "=", "Backspace"};

    QGridLayout * padLayout = new QGridLayout();
    QButtonGroup * group = new QButtonGroup(centralWidget());

    for (int i = Controller::Button_0; i < Controller::Button_Count; i++)
    {
        QPushButton* tmp = new QPushButton(textBox[i]);
        tmp->setShortcut(tr(shortcuts[i]));
        _buttonArray[i] = tmp;
        group->addButton(_buttonArray[i],i);
    }

    for (int i = Controller::Button_A; i <= Controller::Button_F; i++)
    {
        _buttonArray[i]->setEnabled(false);
    }

    padLayout->addWidget(_buttonArray[Controller::Button_E], 0, 0);
    padLayout->addWidget(_buttonArray[Controller::Button_F], 0, 1);
    padLayout->addWidget(_buttonArray[Controller::Button_Clear], Controller::Button_Clear / 4 + 1, 0, 1, 4);

    QComboBox * comboBox = new QComboBox(centralWidget());
    comboBox->addItem("Bin");
    comboBox->addItem("Dec");
    comboBox->addItem("Hex");
    comboBox->setCurrentIndex(1);
    padLayout->addWidget(comboBox, 0, 3);

    padLayout->addWidget(new QLabel("Base", centralWidget()), 0, 2, 1, 1, Qt::AlignRight);

    for (int i = 0; i < Controller::Button_Count - 3; i++)
    {
        padLayout->addWidget(_buttonArray[padOrder[i]], i / 4 + 1, i % 4);
    }

    connect(group, SIGNAL(buttonClicked(int)), this, SLOT(onPadClicked(int)));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(baseChanged(int)));

    connect(new QShortcut(Qt::Key_Return, this), SIGNAL(activated()), _buttonArray[Controller::Button_Equal], SLOT(animateClick()));
    connect(new QShortcut(Qt::Key_Enter, this), SIGNAL(activated()), _buttonArray[Controller::Button_Equal], SLOT(animateClick()));
    connect(new QShortcut(Qt::Key_Comma, this), SIGNAL(activated()), _buttonArray[Controller::Button_Dot], SLOT(animateClick()));
    connect(new QShortcut(Qt::Key_Delete, this), SIGNAL(activated()), _buttonArray[Controller::Button_Clear], SLOT(animateClick()));

    return padLayout;
}
