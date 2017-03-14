/**
 * @file   InvoiceModel.h
 * @author Sebastien Fourey
 *
 * @brief  Invoice document model declaration.
 */
#ifndef _INVOICEMODEL_H_
#define _INVOICEMODEL_H_

#include <iostream>
#include <QObject>
#include <QDataStream>

class InvoiceModel : public QObject {

    Q_OBJECT

    friend QDataStream & operator << (QDataStream & out, const InvoiceModel &);
    friend QDataStream & operator >> (QDataStream & in, InvoiceModel &);

public:

    InvoiceModel();
    InvoiceModel(const InvoiceModel &);

    const static int NB_ROWS = 15;

    const QString & lastname( ) const;

    const QString & firstname( ) const;

    const QString & addressLine1( ) const;

    const QString & addressLine2( ) const;

    const QString & zipcode( ) const;

    const QString & city( ) const;

    const QString & cell( int row, int col ) const;

    const double & taxe() const;

    enum ColumnID { Column_Description = 0, Column_UnitPrice, Column_Quantity, Column_Total, Column_Count };

public slots:

    void setLastname( const QString & lastname );

    void setFirstname( const QString & firstname );

    void setAddressLine1( const QString & text );

    void setAddressLine2( const QString & text );

    void setZipcode( const QString & zipcode );

    void setCity( const QString & city );

    void setCell( int row, int column, const QString & text );

    void clear();

signals:

    void notify();

private:

    QString _lastname;
    QString _firstname;
    QString _addressLine1;
    QString _addressLine2;
    QString _zipcode;
    QString _city;
    QString _cells[NB_ROWS][4];

    const double _taxe = 0.20;
};

QDataStream & operator << (QDataStream & out, const InvoiceModel &);
QDataStream & operator >> (QDataStream & in, InvoiceModel &);

#endif
