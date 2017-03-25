#ifndef ACTIVESUDOKUBOX_H
#define ACTIVESUDOKUBOX_H

#include "SudokuBox.h"

class ActiveSudokuBox : public SudokuBox
{
    Q_OBJECT

public:
    explicit ActiveSudokuBox(int i, int j, QWidget * parent = 0);
    //void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent * evt);

public slots:
    void updateValue(int value);
};

#endif
