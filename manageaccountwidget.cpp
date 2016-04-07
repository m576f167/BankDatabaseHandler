#include "manageaccountwidget.h"
#include "ui_manageaccountwidget.h"

ManageAccountWidget::ManageAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageAccountWidget){

    ui->setupUi(this);

    setMinimumHeight(300);
    setMinimumWidth(500);

    accountTableModel = 0;
    sourceSelected=false;
    transactiondialog = new TransactionDialog;

    connect(transactiondialog, SIGNAL(dialogClosed()), this, SLOT(unsetSource()));

}

ManageAccountWidget::~ManageAccountWidget(){

    delete ui;

}

void ManageAccountWidget::setModel(QSqlTableModel* accountModel, QSqlTableModel* transactionModel){

    accountTableModel = accountModel;
    transactiondialog->setModel(accountModel,transactionModel);

    accountTableModel->select();

    setWindowTitle(trUtf8("Számlák kezelése"));

    setupGui();

}

void ManageAccountWidget::setupGui(){

    ui->accountTableView->setModel(accountTableModel);
    ui->infoLabel->setText("Kattintson egy adott számlára, hogy kiválassza, majd egy másikra az utalás megkezdéséhez!");
    ui->selectionLabel->setText("Nincs forrás számla kiválasztva.");
    ui->accountTableView->setMaximumWidth(425);
    connect(ui->accountTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(selectForTransaction(QModelIndex)));
    ui->accountTableView->resizeColumnsToContents();
    ui->accountTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->accountTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void ManageAccountWidget::selectForTransaction(const QModelIndex& index){

    if (ui->accountTableView->model()->data(ui->accountTableView->model()->index(index.row(), 3), Qt::CheckStateRole).toInt()==Qt::Checked) return;

    if(!sourceSelected){

        sourceSelected=true;
        source=index;
        ui->selectionLabel->setText("Forrás számla kiválasztva: "+ui->accountTableView->model()->data(ui->accountTableView->model()->index(index.row(), 0), Qt::EditRole).toString());

    }else if (source==index) unsetSource();
    else transactiondialog->openTransactionDialog(source,index);

}

void ManageAccountWidget::unsetSource(){

    sourceSelected=false;
    ui->selectionLabel->setText("Nincs forrás számla kiválasztva.");

}
