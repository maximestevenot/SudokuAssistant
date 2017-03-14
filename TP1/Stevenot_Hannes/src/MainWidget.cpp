/**
 * @file   MainWidget.cpp
 * @author Sebastien Fourey
 *
 * @brief  MainWidget methods definitions.
 */

#include "MainWidget.h"
#include <QMouseEvent>
#include <QString>
#include <QMessageBox>
#include <QDateTime>

using namespace std;

MainWidget::MainWidget()
{
    setGeometry(100,100,300,300);
    setWindowTitle("Mets un peu de couleur dans ta vie");

    QLabel *label = new QLabel("Colors, signals, and slots",this);
    label->setGeometry(10,10,290,30);
    label->setFont(QFont("Arial",14,QFont::Bold));

    _lineDisplay = new QLineEdit("",this);
    _lineDisplay->setGeometry(50,70,200,30);
    _lineDisplay->setAlignment(Qt::AlignHCenter);
    _lineDisplay->setReadOnly(true);
    _lineDisplay->move(_lineDisplay->x(), _lineDisplay->y()+40);

    _otherLineDisplay = new QLineEdit("",this);
    _otherLineDisplay->setGeometry(0,0,200,30);
    _otherLineDisplay->setAlignment(Qt::AlignHCenter);
    _otherLineDisplay->move(_lineDisplay->x(), _lineDisplay->y()-35);
    _otherLineDisplay->setReadOnly(true);

    _timeDisplay = new QTimeEdit(this);
    _timeDisplay->setGeometry(0,0,200,30);
    _timeDisplay->setAlignment(Qt::AlignHCenter);
    _timeDisplay->move(_otherLineDisplay->x(), _otherLineDisplay->y()-35);
    _timeDisplay->setReadOnly(true);
    _timeDisplay->setDisplayFormat("HH:mm:ss.zzz");

    _timer = new QTimer(this);
    _timer->setInterval(50);

    ColorWidget *colorWidget = new ColorWidget(this);
    colorWidget->setGeometry(100,160,80,30);

    QPushButton *pushButtonRandomColor = new QPushButton("Random color",this);
    pushButtonRandomColor->setGeometry(60,200,160,30);

    QPushButton *pushButtonQuit = new QPushButton("Quit",this);
    pushButtonQuit->setGeometry(100,250,80,30);

    connect(_timer,SIGNAL(timeout()),
            this,SLOT(showTime()));

    connect(pushButtonQuit,SIGNAL(clicked()),
            this,SLOT(quitPressed()));

    connect(pushButtonRandomColor,SIGNAL(clicked()),
            colorWidget,SLOT(changeColor()));

    connect(colorWidget,SIGNAL(colorChanged(int,int,int)),
            this,SLOT(colorChanged(int,int,int)));

    _timer->start();
}


void MainWidget::mouseMoveEvent(QMouseEvent * e)
{
    QString text("x(%1) y(%2)");
    _otherLineDisplay->setText(text.arg(e->x()).arg(e->y()));

    Qt::Alignment alignment;

    if (e->buttons() & Qt::LeftButton)
    {
        alignment = Qt::AlignLeft;
    }
    else if (e->buttons() & Qt::RightButton)
    {
        alignment = Qt::AlignRight;
    }
    else if (e->buttons() & Qt::MidButton)
    {
        alignment = Qt::AlignCenter;
    }

    _otherLineDisplay->setAlignment(alignment);
    e->accept();
}

void MainWidget::showTime()
{
    _timeDisplay->setTime(QTime::currentTime());
    _timer->start();
}

void MainWidget::quitPressed()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this,
                                   "You want to quit...",
                                   "Are you sure that you want to quit"
                                   " this great application?",
                                   QMessageBox::Yes|QMessageBox::No,
                                   QMessageBox::No );

    if ( button == QMessageBox::Yes )
    {
        close();
    }
}


void MainWidget::colorChanged(int r, int g, int b)
{
    QString text("Color: R(%1) G(%2) B(%3)");
    _lineDisplay->setText(text.arg(r).arg(g).arg(b));
}
