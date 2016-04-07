#include "manageaccountswidget.h"
#include "ui_manageaccountswidget.h"

ManageAccountsWidget::ManageAccountsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageAccountsWidget){

    ui->setupUi(this);

    setMinimumHeight(300);
    setMinimumWidth(500);

    accountTableModel = 0;
    transactionTableModel = 0;

}

ManageAccountsWidget::~ManageAccountsWidget(){

    delete ui;

}

void ManageAccountsWidget::setModel(QSqlTableModel* accountModel, QSqlTableModel* transactionModel){

    accountTableModel = accountModel;
    transactionTableModel = transactionModel;

    accountTableModel->select();

    setWindowTitle(trUtf8("Számlák kezelése"));

    setupGui();

}

void ManageAccountsWidget::setupGui(){

    ui->accountTableView->setModel(accountTableModel);
    ui->infoLabel->setText("Kattintson egy adott számlára, hogy kiválassza, majd egy másikra az utalás megkezdéséhez!");
    ui->accountTableView->setMaximumWidth(415);
    //connect(ui->dataTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accountTableView_DoubleClicked(QModelIndex)));
    ui->accountTableView->resizeColumnsToContents();
    ui->accountTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->accountTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}
