#include "clienttablemodel.h"

ClientTableModel::ClientTableModel(QObject *parent) : QSqlRelationalTableModel(parent){

    setupModel();

}

void ClientTableModel::setupModel(){

    setTable("clients");
    setSort(0, Qt::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(0, Qt::Horizontal, trUtf8("Név"));
    setHeaderData(1, Qt::Horizontal, trUtf8("Cím"));
    setHeaderData(2, Qt::Horizontal, trUtf8("Telefonszám"));
    //setRelation(1, QSqlRelation("building", "id", "name"));

}

