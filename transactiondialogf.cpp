#include "transactiondialogf.h"
#include <QMessageBox>
#include <QDialogButtonBox>

TransactionDialog::TransactionDialog(QWidget *parent) : QDialog(parent){

    accountTableModel=0;
    sendButton=0;
    cancelButton=0;
    amountEdit=0;
    sourceLabel=0;
    targetLabel=0;

}

void TransactionDialog::setModel(QSqlTableModel* accountTable){

    accountTableModel=accountTable;

}

void TransactionDialog::openTransactionDialog(QModelIndex source, QModelIndex target){

    if(sendButton!=0) delete sendButton;
    if(cancelButton!=0) delete cancelButton;
    if(amountEdit!=0) delete amountEdit;
    if(sourceLabel!=0) delete sourceLabel;
    if(targetLabel!=0) delete targetLabel;


    setWindowTitle(trUtf8("Utalás"));

    mainLayout=new QVBoxLayout;
    sourceLabel=new QLabel;
    sourceLabel->setText("Küldő számlaszáma: "+accountTableModel->data(accountTableModel->index(source.row(), 0), Qt::EditRole).toString());

    targetLabel=new QLabel;
    targetLabel->setText("Cél számlaszáma: "+accountTableModel->data(accountTableModel->index(target.row(), 0), Qt::EditRole).toString());

    mainLayout->addWidget(sourceLabel);
    mainLayout->addWidget(targetLabel);

    QHBoxLayout* amountLayout=new QHBoxLayout;
    amountLayout->addWidget(new QLabel(trUtf8("Összeg:")));
    amountEdit=new QLineEdit;
    amountLayout->addWidget(amountEdit);

    QHBoxLayout* buttonsLayout=new QHBoxLayout;
    sendButton=new QPushButton(trUtf8("Küldés"), this);
    cancelButton=new QPushButton(trUtf8("Mégse"), this);
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    buttonsLayout->addWidget(sendButton);
    buttonsLayout->addWidget(cancelButton);

    mainLayout->addLayout(amountLayout);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
    show();

}

void TransactionDialog::sendButtonClicked(){




}

