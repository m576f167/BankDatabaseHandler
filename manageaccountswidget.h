#ifndef MANAGEACCOUNTSWIDGET_H
#define MANAGEACCOUNTSWIDGET_H

#include <QWidget>
#include <QSqlTableModel>


namespace Ui {
class ManageAccountsWidget;
}

class ManageAccountsWidget : public QWidget{
    Q_OBJECT

public:

    explicit ManageAccountsWidget(QWidget *parent = 0);
    ~ManageAccountsWidget();

    void setModel(QSqlTableModel* accountModel, QSqlTableModel* transactionModel);

private slots:


private:

    void setupGui();

    QSqlTableModel* accountTableModel;
    QSqlTableModel* transactionTableModel;

    Ui::ManageAccountsWidget *ui;

};

#endif // MANAGEACCOUNTSWIDGET_H
