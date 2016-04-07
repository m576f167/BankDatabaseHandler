#ifndef ACCOUNTTABLEMODEL_H
#define ACCOUNTTABLEMODEL_H

#include <QSqlRelationalTableModel>
#include <QMap>
#include <QVector>

class AccountTableModel : public QSqlRelationalTableModel{
    Q_OBJECT

public:

    AccountTableModel(QSqlTableModel* transactionTable, QObject* parent=0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:

    void addTransaction(int source, int target, int difference);

private:

    int columnCount(const QModelIndex& parent) const;
    void setupModel();
    void calculateBalance();
    QSqlTableModel* transactionTableModel;
    QMap<int,int> accountBalance;
    QVector<int*> balancePointers;

};

#endif // ACCOUNTTABLEMODEL_H
