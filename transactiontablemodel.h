#ifndef TRANSACTIONTABLEMODEL_H
#define TRANSACTIONTABLEMODEL_H

#include <QSqlRelationalTableModel>

class TransactionTableModel : public QSqlRelationalTableModel{
    Q_OBJECT

public:

    TransactionTableModel(QObject* parent=0);

private:

    void setupModel();

};

#endif // TRANSACTIONTABLEMODEL_H
