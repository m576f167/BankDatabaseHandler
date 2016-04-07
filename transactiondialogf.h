#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSqlTableModel>
#include <QGridLayout>

class TransactionDialog : public QDialog{
    Q_OBJECT

public:

    TransactionDialog(QWidget *parent = 0);

    void setModel(QSqlTableModel* accountTable);
    void openTransactionDialog(QModelIndex source, QModelIndex target);

private slots:

    void sendButtonClicked();

private:

    QSqlTableModel* accountTableModel;

    QVBoxLayout* mainLayout;
    QPushButton* sendButton;
    QPushButton* cancelButton;
    QLineEdit* amountEdit;
    QLabel* sourceLabel;
    QLabel* targetLabel;

};

#endif // TRANSACTIONDIALOG_H
