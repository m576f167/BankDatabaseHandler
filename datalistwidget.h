#ifndef DATALISTWIDGET_H
#define DATALISTWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

namespace Ui {
class DataListWidget;
}

enum table{client, account, transaction};

class DataListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataListWidget(QWidget *parent = 0);
    ~DataListWidget();

    void setModel(QSqlTableModel* clientModel, QSqlTableModel* accountModel, QSqlTableModel* transactionModel, table type);

signals:

    void updateAccounts(int source, int target, int amount);

private slots:

    void clientTableView_DoubleClicked(const QModelIndex& index);
    void accountTableView_DoubleClicked(const QModelIndex& index);
    void transactionTableView_DoubleClicked(const QModelIndex& index);

private:

    void setupGui(table type);

    QSqlTableModel* clientTableModel;
    QSqlTableModel* accountTableModel;
    QSqlTableModel* transactionTableModel;

    QSqlQueryModel* filteredAccounts;
    QSqlQueryModel* filteredTransactions;

    QSortFilterProxyModel* accountFilter;
    QSortFilterProxyModel* transactionFilter;


    Ui::DataListWidget *ui;
};


#endif // DATALISTWIDGET_H
