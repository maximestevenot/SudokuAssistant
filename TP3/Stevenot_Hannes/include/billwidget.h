/**
 * @file   billwidget.h
 * @author Guillaume Hannes
 * @author Maxime Stevenot
 */

#ifndef BILLWIDGET_H
#define BILLWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QRectF>
#include "InvoiceModel.h"

class BillWidget : public QWidget
{
    Q_OBJECT

public:

    explicit BillWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void setDocument(InvoiceModel *);

private:

    InvoiceModel * _model;

    QRectF _contactRectangle;
    QRectF _totalRectangle;
    QRectF _taxesRectangle;
    QVector<QRectF> _tableHeaders;

    void drawTopRect(QPainter &);
    void drawTableRect(QPainter &);
    void drawBottomRect(QPainter &);
    void drawContactInformation(QPainter &);
    void drawTableContent(QPainter &);

    static const qreal MARGIN;
    static const qreal TOP_RECT_WIDTH;
    static const qreal TOP_RECT_HEIGHT;
    static const qreal TABLE_ROW_HEIGHT;
    qreal TABLE_COLUMN_WIDTH;
};

#endif
