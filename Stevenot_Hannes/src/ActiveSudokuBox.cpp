#include "ActiveSudokuBox.h"
#include <QPainter>
#include <QPen>
#include <QFont>

ActiveSudokuBox::ActiveSudokuBox(int i, int j, QWidget *parent) : SudokuBox(i, j, parent) { }

void ActiveSudokuBox::paintEvent(QPaintEvent * evt)
{
    SudokuBox::paintEvent(evt);

}

void ActiveSudokuBox::updateValue(int value)
{
    QPainter painter(this);

    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.setPen(QPen(QColor(Qt::blue)));

    QString displayedContent;
    if (value)
    {
        displayedContent = QString::number(value);
    }
    painter.drawText(rect(), Qt::AlignVCenter | Qt::AlignCenter, displayedContent);
}

void ActiveSudokuBox::mouseReleaseEvent(QMouseEvent * evt)
{
    emit onMouseClicked(iIndex(), jIndex());
    evt->accept();
}
