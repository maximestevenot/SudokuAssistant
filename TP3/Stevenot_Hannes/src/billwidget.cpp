/**
 * @file   billwidget.cpp
 * @author Guillaume Hannes
 * @author Maxime Stevenot
 */

#include "billwidget.h"
#include <QRectF>
#include <QBrush>
#include <QDebug>

const qreal BillWidget::MARGIN = 10;
const qreal BillWidget::TOP_RECT_WIDTH = 280;
const qreal BillWidget::TOP_RECT_HEIGHT = BillWidget::TOP_RECT_WIDTH / 3;
const qreal BillWidget::TABLE_ROW_HEIGHT = 30;

BillWidget::BillWidget(QWidget *parent) :
    QWidget(parent)
{
}

void BillWidget::setDocument(InvoiceModel * m) {
    _model = m;
    connect(_model, SIGNAL(notify()), this, SLOT(update()));
}

void BillWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    TABLE_COLUMN_WIDTH = width() / 6;

    drawTopRect(painter);
    drawTableRect(painter);
    drawBottomRect(painter);

    drawContactInformation(painter);
    drawTableContent(painter);

    painter.end();
}

void BillWidget::drawContactInformation(QPainter & painter)
{
    if (!_model) {
        return;
    }

    QString  fName = _model->firstname();
    QString  lName = _model->lastname();
    QString  add1 = _model->addressLine1();
    QString  add2 = _model->addressLine2();
    QString  zCode = _model->zipcode();
    QString  city = _model->city();

    QString info = fName + " " + lName + "\n";
    info += add1 + "\n" + add2 + "\n";
    info += zCode + " " + city;

    painter.drawText(_contactRectangle, Qt::AlignLeft, info);
}

void BillWidget::drawTableContent(QPainter & painter)
{
    int contentH = TABLE_ROW_HEIGHT + (TABLE_ROW_HEIGHT + 12);

    for (int i = 0; i < InvoiceModel::NB_ROWS; i++)
    {
        for (int j = 0; j < InvoiceModel::Column_Count; j++)
        {
            QRectF rect = _tableHeaders[j].adjusted(MARGIN, contentH, 0, 0);
            painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, _model->cell(i,j));

        }
        contentH += (TABLE_ROW_HEIGHT + 12);
    }


    double totalPrice = 0;

    for (int i = 0; i < InvoiceModel::NB_ROWS; i++)
    {
        double unitPrice = _model->cell(i,1).toDouble();
        double realPrice = unitPrice + _model->taxe() * unitPrice;
        totalPrice += realPrice * _model->cell(i,2).toDouble();
    }

    QString taxe = QString::number(_model->taxe() * 100) + "%";
    painter.drawText(_taxesRectangle, Qt::AlignVCenter | Qt::AlignRight, taxe);
    painter.drawText(_totalRectangle, Qt::AlignVCenter | Qt::AlignRight, QString::number(totalPrice) + tr(" $"));

}

void BillWidget::drawTopRect(QPainter & painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(QBrush(QColor(105, 190, 222)));

    QRectF topRect(MARGIN, MARGIN, TOP_RECT_WIDTH, TOP_RECT_HEIGHT);
    painter.drawRoundedRect(topRect, 10, 10, Qt::RelativeSize);
    _contactRectangle = topRect.adjusted(MARGIN, MARGIN, -MARGIN, -MARGIN);
}

void BillWidget::drawBottomRect(QPainter & painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(QBrush(QColor(211, 215, 216)));

    int x = width() -TABLE_COLUMN_WIDTH-MARGIN;
    int y = height() - TABLE_ROW_HEIGHT - 2 *MARGIN;

    QRectF totalRect(x, y, TABLE_COLUMN_WIDTH, TABLE_ROW_HEIGHT);
    QRectF taxesRect(x, y - 5 * MARGIN, TABLE_COLUMN_WIDTH, TABLE_ROW_HEIGHT);

    _totalRectangle = totalRect.adjusted(0,0, - MARGIN / 2, 0);
    _taxesRectangle = taxesRect.adjusted(0,0, - MARGIN / 2, 0);

    QRectF totalLabel(x - 1.5 * TABLE_COLUMN_WIDTH, y, 2 * TABLE_COLUMN_WIDTH, TABLE_ROW_HEIGHT);
    QRectF taxesLabel(x - 1.5 * TABLE_COLUMN_WIDTH, y - 5 * MARGIN, 2 * TABLE_COLUMN_WIDTH, TABLE_ROW_HEIGHT);

    painter.drawText(totalLabel, Qt::AlignVCenter | Qt::AlignLeft, tr("Total (w. taxes)"));
    painter.drawText(taxesLabel, Qt::AlignVCenter | Qt::AlignLeft, tr("Taxes"));

    painter.drawRect(totalRect);
    painter.drawRect(taxesRect);
}

void BillWidget::drawTableRect(QPainter & painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(QBrush(QColor(211, 215, 216)));

    _tableHeaders = QVector<QRectF>();
    const QString headersText[] = {tr("Item"), tr("Unit Price"), tr("Quantity"), tr("Price")};
    QVector<QRectF> table = QVector<QRectF>();

    qreal marginLeft = width() - 2 * MARGIN - 3 * TABLE_COLUMN_WIDTH;

    // First Column Header
    QRectF temp(MARGIN, TOP_RECT_HEIGHT + 3*MARGIN, marginLeft, TABLE_ROW_HEIGHT);
    _tableHeaders.append(temp);
    table.append(temp);

    // First Column Content
    table.append(QRectF(MARGIN, TOP_RECT_HEIGHT + 3*MARGIN + TABLE_ROW_HEIGHT, marginLeft, 15*TABLE_ROW_HEIGHT));

    marginLeft += MARGIN;
    for (int i = 0; i < 3; i++)
    {
        // Header
        QRectF temp2(marginLeft, TOP_RECT_HEIGHT + 3*MARGIN, TABLE_COLUMN_WIDTH, TABLE_ROW_HEIGHT);
        table.append(temp2);
        _tableHeaders.append(temp2);

        // Content
        table.append(QRectF(marginLeft, TOP_RECT_HEIGHT + 3*MARGIN + TABLE_ROW_HEIGHT, TABLE_COLUMN_WIDTH, 15*TABLE_ROW_HEIGHT));
        marginLeft += TABLE_COLUMN_WIDTH;
    }

    painter.drawRects(table);

    for (int i = 0; i < InvoiceModel::Column_Count; ++i)
    {
        painter.drawText(_tableHeaders[i], Qt::AlignCenter, headersText[i]);
    }
}


