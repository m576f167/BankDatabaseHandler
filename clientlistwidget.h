#ifndef CLIENTLISTWIDGET_H
#define CLIENTLISTWIDGET_H

#include <QWidget>
#include <QWidget>
#include <QSqlTableModel>
#include <QItemSelectionModel>

namespace Ui {
class ClientListWidget;
}

enum table{client, account, transaction};

class ClientListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientListWidget(QWidget *parent = 0);
    ~ClientListWidget();

    void setModel(QSqlTableModel* clientModel, QSqlTableModel* accountModel, QSqlTableModel* transactionModel, table type);

private slots:

    void clientTableView_DoubleClicked(const QModelIndex& index);
    void accountTableView_DoubleClicked(const QModelIndex& index);
    void transactionTableView_DoubleClicked(const QModelIndex& index);

private:

    void setupGui(table type);

    QSqlTableModel* clientTableModel;
    QSqlTableModel* accountTableModel;
    QSqlTableModel* transactionTableModel;

    Ui::ClientListWidget *ui;
};

#endif // CLIENTLISTWIDGET_H
