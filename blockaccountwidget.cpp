#include "blockaccountwidget.h"
#include "ui_blockaccountwidget.h"
#include <QSqlQuery>
#include <qDebug>

BlockAccountWidget::BlockAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockAccountWidget){

    ui->setupUi(this);

    setMinimumHeight(300);
    setMinimumWidth(500);

    accountTableModel = 0;

}

BlockAccountWidget::~BlockAccountWidget(){

    delete ui;

}

void BlockAccountWidget::setModel(QSqlTableModel* accountModel){

    accountTableModel = accountModel;
    accountTableModel->select();

    setWindowTitle(trUtf8("Számlák blokkolása/feloldása"));

    setupGui();

}

void BlockAccountWidget::setupGui(){

    ui->accountTableView->setModel(accountTableModel);
    ui->infoLabel->setText("Kattintson egy adott számlára, hogy blokkolja vagy feloldja!");
    ui->accountTableView->setMaximumWidth(425);
    connect(ui->accountTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(changeAccount(QModelIndex)));
    ui->accountTableView->resizeColumnsToContents();
    ui->accountTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->accountTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void BlockAccountWidget::changeAccount(const QModelIndex& index){

    QString number=accountTableModel->data(accountTableModel->index(index.row(),0)).toString();
    bool blocked=(ui->accountTableView->model()->data(ui->accountTableView->model()->index(index.row(), 3), Qt::CheckStateRole).toInt()==Qt::Checked);

    if (blocked){

        QSqlQuery query;
        query.exec("UPDATE accounts SET blocked = 0 WHERE accounts.number = "+number+";");

    }else{

        QSqlQuery query;
        query.exec("UPDATE accounts SET blocked = 1 WHERE accounts.number = "+number+";");

    }

    accountTableModel->select();

}
