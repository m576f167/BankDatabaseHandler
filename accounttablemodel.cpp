#include "accounttablemodel.h"
#include <qDebug>

AccountTableModel::AccountTableModel(QSqlTableModel* transactionTable,QObject *parent) : QSqlRelationalTableModel(parent){

    transactionTableModel=transactionTable;
    setupModel();

}

QVariant AccountTableModel::data(const QModelIndex &index, int role) const{

    if(!index.isValid()) return QVariant();

    if (index.column() == 3){

        switch (role){

            case Qt::TextAlignmentRole:
                return QVariant(Qt::AlignCenter | Qt::AlignVCenter);

            case Qt::CheckStateRole:
                if (QSqlRelationalTableModel::data(index, Qt::DisplayRole).toInt() == 0)
                    return QVariant(Qt::Unchecked);
                else
                    return QVariant(Qt::Checked);

            default:
                return QVariant();
        }

    }else if (index.column() == 4){

        switch (role){

            case Qt::TextAlignmentRole:
                return QVariant(Qt::AlignCenter | Qt::AlignVCenter);

            case Qt::DisplayRole:
                return QVariant(*balancePointers[index.row()]);

            case Qt::EditRole:
                return QVariant(*balancePointers[index.row()]);

            default:
                return QVariant();
        }

    }else return QSqlRelationalTableModel::data(this->index(index.row(), index.column()), role);

}

void AccountTableModel::setupModel(){

    setTable("accounts");
    setSort(1, Qt::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(0, Qt::Horizontal, trUtf8("Számlaszám"));
    setHeaderData(1, Qt::Horizontal, trUtf8("Kliens neve"));
    setHeaderData(2, Qt::Horizontal, trUtf8("Nyitási dátum"));
    setHeaderData(3, Qt::Horizontal, trUtf8("Blokkolt-e"));
    insertColumn(4);
    setHeaderData(4, Qt::Horizontal, trUtf8("Egyenleg"));
    select();

    calculateBalance();

}

int AccountTableModel::columnCount(const QModelIndex& parent) const{

    return QSqlTableModel::columnCount(parent) + 1;

}

void AccountTableModel::calculateBalance(){


    for(int i=0; i<rowCount(); ++i){

        int nextIndex=index(i,0).data().toInt();
        accountBalance[nextIndex]=100000;

        int* next=&accountBalance[nextIndex];
        balancePointers.push_back(next);

    }

    for (int i=0; i<transactionTableModel->rowCount(); ++i){

        int difference=transactionTableModel->index(i,2).data().toInt();
        int source=transactionTableModel->index(i,3).data().toInt();
        int target=transactionTableModel->index(i,4).data().toInt();


        accountBalance[source]-=difference;
        accountBalance[target]+=difference;

    }

}

void AccountTableModel::addTransaction(int source, int target, int difference){

    accountBalance[source]-=difference;
    accountBalance[target]+=difference;
    select();

}
