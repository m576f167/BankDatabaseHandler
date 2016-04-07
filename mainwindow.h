#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QSqlTableModel>
#include "datalistwidget.h"
#include "manageaccountwidget.h"
#include "accounttablemodel.h"
#include "blockaccountwidget.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event); // ablak bezárása

private slots:
    void viewClients_Triggered();
    void viewAccounts_Triggered();
    void viewTransactions_Triggered();
    void addTransaction_Triggered();
    void blockAccount_Triggered();
    void updateAccountsTable(int source, int target, int amount);

private:
    void setupMenu();
    void setupModels();

    QMdiArea* mdiArea;
    QMenu* viewMenu;
    QMenu* actionMenu;

    QAction* viewClients;
    QAction* viewAccounts;
    QAction* viewTransactions;

    QAction* addTransaction;
    QAction* blockAccount;

    QSqlTableModel* clientTableModel;
    AccountTableModel* accountTableModel;
    QSqlTableModel* transactionTableModel;

    DataListWidget* datalistwidget;
    ManageAccountWidget* manageaccountwidget;
    BlockAccountWidget* blockaccountwidget;

};

#endif // MAINWINDOW_H
