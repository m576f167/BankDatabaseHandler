#include "clientlistwidget.h"
#include "ui_clientlistwidget.h"
#include <QSqlQuery>
#include <QMessageBox>

ClientListWidget::ClientListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientListWidget){

    ui->setupUi(this);

    clientTableModel = 0;
    accountTableModel = 0;
    transactionTableModel = 0;

    setWindowTitle(trUtf8("Kliensek listázása"));

}

ClientListWidget::~ClientListWidget(){

    delete ui;

}

void ClientListWidget::setModel(QSqlTableModel* clientModel, QSqlTableModel* accountModel, QSqlTableModel* transactionModel, table type){

    clientTableModel = clientModel;
    accountTableModel = accountModel;
    transactionTableModel = transactionModel;

    clientTableModel->select();
    /*QSqlQuery query;
    query.exec("select * from accounts where client_id=1;");
    accountTableModel->setQuery(query);*/
    accountTableModel->select();
    transactionTableModel->select();

    setupGui(type);

}

void ClientListWidget::setupGui(table type){

    switch (type){

        case client:
            ui->clientTableView->setModel(clientTableModel);
            connect(ui->clientTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(clientTableView_DoubleClicked(QModelIndex)));
            break;

        case account:
            ui->clientTableView->setModel(accountTableModel);
            connect(ui->clientTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accountTableView_DoubleClicked(QModelIndex)));
            break;

        case transaction:
            ui->clientTableView->setModel(transactionTableModel);
            connect(ui->clientTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(transactionTableView_DoubleClicked(QModelIndex)));
            break;

    }

    ui->clientTableView->resizeColumnsToContents();
    ui->clientTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->clientTableView->setSelectionModel(buildingSelectionModel); // szelekciós modell megadása
    ui->clientTableView->setColumnHidden(0, true);

}

void ClientListWidget::clientTableView_DoubleClicked(const QModelIndex& index){

    //szűrés és utána:
    setupGui(account);

}

void ClientListWidget::accountTableView_DoubleClicked(const QModelIndex& index){

    //szűrés és utána:
    setupGui(transaction);

}

void ClientListWidget::transactionTableView_DoubleClicked(const QModelIndex& index){

    //sztornózás

}
