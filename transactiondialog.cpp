#include "transactiondialog.h"
#include "ui_transactiondialog.h"
#include <limits>
#include <QMessageBox>
#include <QSqlQuery>
#include <qDebug>

TransactionDialog::TransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionDialog){

    ui->setupUi(this);

}

TransactionDialog::~TransactionDialog(){

    delete ui;

}

void TransactionDialog::setModel(QSqlTableModel* accountTable, QSqlTableModel* transactionTable){

    accountTableModel=accountTable;
    transactionTableModel=transactionTable;

}

void TransactionDialog::openTransactionDialog(QModelIndex source, QModelIndex target){

    setWindowTitle(trUtf8("Utalás"));

    sourceStr=accountTableModel->data(accountTableModel->index(source.row(), 0), Qt::EditRole).toString();
    targetStr=accountTableModel->data(accountTableModel->index(target.row(), 0), Qt::EditRole).toString();

    ui->sourceLabel->setText("Küldő számlaszáma: "+sourceStr);
    ui->targetLabel->setText("Cél számlaszáma: "+targetStr);

    ui->amountEdit->setText("");
    ui->amountEdit->setValidator(new QIntValidator(1, std::numeric_limits<int>::max(), this));


    ui->errorLabel->setStyleSheet("QLabel { color : red; }");
    ui->errorLabel->setText("");

    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendButtonClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(finish()));

    show();

}

void TransactionDialog::sendButtonClicked(){

    QString amount=ui->amountEdit->text();

    int i=0;

    while(sourceStr!=accountTableModel->data(accountTableModel->index(i, 0), Qt::EditRole).toString()) ++i;

    QString sourceBalance=accountTableModel->data(accountTableModel->index(i, 4), Qt::EditRole).toString();

    if (amount.toInt()>sourceBalance.toInt())
        ui->errorLabel->setText("Hiba! A "+sourceStr+" számlán\ncsak "+sourceBalance+" dollár van.");
    else if(amount=="")
        ui->errorLabel->setText("Hiba! Nincs öszzeg megadva.");
    else{

        if (QMessageBox::question(this, trUtf8("Megerősítés"), "Biztosan el akar utalni "+amount+" dollárt\na "+sourceStr+" számláról a "+targetStr+" számlára?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){

            addTransactionToTable(amount);
            emit updateAccounts(sourceStr.toInt(),targetStr.toInt(),amount.toInt());
            finish();

        }

    }

}

void TransactionDialog::finish(){

    emit dialogClosed();
    close();

}

void TransactionDialog::addTransactionToTable(QString amount){

    int id=transactionTableModel->data(transactionTableModel->index(transactionTableModel->rowCount()-1, 0), Qt::EditRole).toInt();
    QString newID;
    newID=QString::number(id+1);
    QSqlQuery query;
    query.exec("INSERT INTO transaction (id, date, amount, source, objective) VALUES ("+newID+", NOW(), "+amount+", '"+sourceStr+"', '"+targetStr+"');");
    transactionTableModel->select();

}
