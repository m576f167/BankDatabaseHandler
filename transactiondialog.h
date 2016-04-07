#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QSqlTableModel>
#include <QGridLayout>

namespace Ui {
class TransactionDialog;
}

class TransactionDialog : public QDialog
{
    Q_OBJECT

public:

    TransactionDialog(QWidget *parent = 0);
    ~TransactionDialog();

    void setModel(QSqlTableModel* accountTable, QSqlTableModel* transactionTable);
    void openTransactionDialog(QModelIndex source, QModelIndex target);

signals:

    void updateAccounts(int source, int target, int amount);
    void dialogClosed();

private slots:

    void sendButtonClicked();
    void finish();

private:

    void addTransactionToTable(QString amount);

    QString sourceStr;
    QString targetStr;
    QSqlTableModel* accountTableModel;
    QSqlTableModel* transactionTableModel;
    Ui::TransactionDialog *ui;

};

#endif // TRANSACTIONDIALOG_H
