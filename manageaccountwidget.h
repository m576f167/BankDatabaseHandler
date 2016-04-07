#ifndef MANAGEACCOUNTWIDGET_H
#define MANAGEACCOUNTWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include "transactiondialog.h"

namespace Ui {
class ManageAccountWidget;
}

class ManageAccountWidget : public QWidget{
    Q_OBJECT

public:

    explicit ManageAccountWidget(QWidget *parent = 0);
    ~ManageAccountWidget();

    void setModel(QSqlTableModel* accountModel, QSqlTableModel* transactionModel);
    TransactionDialog* transactiondialog;

private slots:

    void selectForTransaction(const QModelIndex& index);
    void unsetSource();

private:

    bool sourceSelected;

    void setupGui();

    QSqlTableModel* accountTableModel;
    QModelIndex source;

    Ui::ManageAccountWidget *ui;
};

#endif // MANAGEACCOUNTWIDGET_H
