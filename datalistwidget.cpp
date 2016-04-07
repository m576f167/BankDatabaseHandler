#include "datalistwidget.h"
#include "ui_datalistwidget.h"
#include <QSqlQuery>
#include <qDebug>
#include <QMessageBox>
#include <QString>

DataListWidget::DataListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataListWidget){

    ui->setupUi(this);

    setMinimumHeight(300);
    setMinimumWidth(500);

    clientTableModel = 0;
    accountTableModel = 0;
    transactionTableModel = 0;
    accountFilter = new QSortFilterProxyModel();
    transactionFilter = new QSortFilterProxyModel();

}

DataListWidget::~DataListWidget(){

    delete accountFilter;
    delete transactionFilter;
    delete ui;

}

void DataListWidget::setModel(QSqlTableModel* clientModel, QSqlTableModel* accountModel, QSqlTableModel* transactionModel, table type){

    clientTableModel = clientModel;
    accountTableModel = accountModel;
    transactionTableModel = transactionModel;

    clientTableModel->select();
    accountTableModel->select();
    transactionTableModel->select();

    switch(type){

        case client:

            ui->dataTableView->setModel(clientTableModel);
            break;

        case account:

            ui->dataTableView->setModel(accountTableModel);
            break;

        case transaction:

            ui->dataTableView->setModel(transactionTableModel);
            break;

    }

    setupGui(type);

}

void DataListWidget::setupGui(table type){

    switch (type){

        case client:
            setWindowTitle(trUtf8("Kliensek listázása"));
            ui->infoLabel->setText("Kattintson egy adott kliensre a számlái megtekintéséhez!");
            ui->dataTableView->setMaximumWidth(470);
            connect(ui->dataTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(clientTableView_DoubleClicked(QModelIndex)));
            break;

        case account:
            setWindowTitle(trUtf8("Számlák listázása"));
            ui->infoLabel->setText("Kattintson egy adott számlára a tranzakciók megtekintéséhez!");
            ui->dataTableView->setMaximumWidth(425);
            connect(ui->dataTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accountTableView_DoubleClicked(QModelIndex)));
            break;

        case transaction:
            setWindowTitle(trUtf8("Tranzakciók listázása"));
            ui->infoLabel->setText("Kattintson egy adott tranzakcióra a stornózáshoz!");
            ui->dataTableView->setMaximumWidth(240);
            connect(ui->dataTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(transactionTableView_DoubleClicked(QModelIndex)));
            ui->dataTableView->setColumnHidden(0, true);
            break;

    }

    ui->resultLabel->setText("");
    ui->dataTableView->resizeColumnsToContents();
    ui->dataTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dataTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void DataListWidget::clientTableView_DoubleClicked(const QModelIndex& index){

    disconnect(ui->dataTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(clientTableView_DoubleClicked(QModelIndex)));

    if (index.isValid()){

        QAbstractItemModel* model=ui->dataTableView->model();

        accountFilter->setSourceModel(accountTableModel);
        accountFilter->setFilterKeyColumn(1);
        accountFilter->setFilterFixedString(model->data(model->index(index.row(), 0), Qt::EditRole).toString());

        ui->dataTableView->setModel(accountFilter);

    }else{

        ui->dataTableView->setModel(accountTableModel);

    }

    setupGui(account);

}

void DataListWidget::accountTableView_DoubleClicked(const QModelIndex& index){

    disconnect(ui->dataTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accountTableView_DoubleClicked(QModelIndex)));

    if (index.isValid()){

        QAbstractItemModel* model=ui->dataTableView->model();

        transactionFilter->setSourceModel(transactionTableModel);
        transactionFilter->setFilterKeyColumn(3);
        transactionFilter->setFilterFixedString(model->data(model->index(index.row(), 0), Qt::EditRole).toString());

        ui->dataTableView->setModel(transactionFilter);

    }else{

        ui->dataTableView->setModel(transactionTableModel);

    }

    setupGui(transaction);

}

void DataListWidget::transactionTableView_DoubleClicked(const QModelIndex& index){

    QAbstractItemModel* model=ui->dataTableView->model();

    QString amount=model->data(model->index(index.row(),2)).toString();
    QString target=model->data(model->index(index.row(),3)).toString();
    QString source=model->data(model->index(index.row(),4)).toString();

    int i=0;

    while(accountTableModel->data(accountTableModel->index(i,0)).toString()!=source) ++i;

    QString sourceBalance=accountTableModel->data(accountTableModel->index(i,4)).toString();
    bool sourceBlocked=(accountTableModel->data(accountTableModel->index(i, 3), Qt::CheckStateRole).toInt()==Qt::Checked);

    i=0;

    while(accountTableModel->data(accountTableModel->index(i,0)).toString()!=target) ++i;

    bool targetBlocked=(accountTableModel->data(accountTableModel->index(i, 3), Qt::CheckStateRole).toInt()==Qt::Checked);

    if (sourceBlocked){ui->resultLabel->setText("Hiba! A "+source+" forrásszámla blokkolva van."); return;}
    if (targetBlocked){ui->resultLabel->setText("Hiba! A "+target+" célszámla blokkolva van."); return;}

    if(sourceBalance.toInt()<amount.toInt()) ui->resultLabel->setText("Hiba! A "+source+" forrásszámlán csak "+sourceBalance+" dollár van.");
    else{

        if (QMessageBox::question(this, trUtf8("Megerősítés"), "Biztosan el akar utalni "+amount+" dollárt\na "+source+" számláról a "+target+" számlára?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){

            emit updateAccounts(source.toInt(),target.toInt(),amount.toInt());

            int id=transactionTableModel->data(transactionTableModel->index(transactionTableModel->rowCount()-1, 0), Qt::EditRole).toInt();
            QString newID;
            newID=QString::number(id+1);
            QSqlQuery query;
            query.exec("INSERT INTO transaction (id, date, amount, source, objective) VALUES ("+newID+", NOW(), "+amount+", '"+source+"', '"+target+"');");
            transactionTableModel->select();

            ui->resultLabel->setText("Sikeres sztornózás.");

        }

    }

}
