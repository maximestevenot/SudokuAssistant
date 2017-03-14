/**
 * @file   ColorWidget.h
 * @author Sebastien Fourey
 *
 * @brief  Simple widget class used as a colored rectangle.
 * Provides a slot which randomly changes the background color.
 */
#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QPen>
#include <QColor>
#include <QPainter>

/**
 * Simple widget class that simply displays a background color.
 */
class ColorWidget : public QWidget {

    Q_OBJECT   // Tell "moc" that this is a signal sender or receiver.

public:

    /**
   * Constructor.
   *
   * @param parent The parent widget.
   */
    ColorWidget(QWidget *parent = 0);

    /**
   * (virtual) Destructor.
   */
    ~ColorWidget() { }

protected:

    /**
   * Virtual method which handles redrawing requests for the widget.
   * @param e The paint event.
   */
    void paintEvent(QPaintEvent* e);

public slots: 

    /**
   * Randomly changes the background color.
   */
    void changeColor();

signals: 

    /**
   * Signal to the "outside" the new color we display.
   *
   * @param r The red component in [0..255].
   * @param g The green component in [0..255].
   * @param b The blue component in [0..255].
   */
    void colorChanged(int r, int g, int b);

private:

    QColor _bgColor;		/**< The background color */
};

#endif


