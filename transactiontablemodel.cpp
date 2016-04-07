#include "transactiontablemodel.h"

TransactionTableModel::TransactionTableModel(QObject *parent) : QSqlRelationalTableModel(parent){

    setupModel();

}

void TransactionTableModel::setupModel(){

    setTable("transaction");
    setSort(1, Qt::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(0, Qt::Horizontal, trUtf8("Azonosító"));
    setHeaderData(1, Qt::Horizontal, trUtf8("Dátum"));
    setHeaderData(2, Qt::Horizontal, trUtf8("Összeg"));
    setHeaderData(3, Qt::Horizontal, trUtf8("Forrás"));
    setHeaderData(4, Qt::Horizontal, trUtf8("Cél"));

}

