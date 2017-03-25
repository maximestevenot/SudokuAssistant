#ifndef INACTIVESUDOKUBOX_H
#define INACTIVESUDOKUBOX_H

#include "SudokuBox.h"

namespace SudokuAssistant {
namespace View {

class InactiveSudokuBox : public SudokuBox
{
    Q_OBJECT

public:
    explicit InactiveSudokuBox(int i, int j, int value = 0, QWidget * parent = 0);
    void paintEvent(QPaintEvent *);

public slots:
    void updateValue(int value);

};

}
}
#endif
