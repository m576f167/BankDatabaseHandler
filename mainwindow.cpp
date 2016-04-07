#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QSqlRelationalTableModel>
#include <QMessageBox>

#include "clienttablemodel.h"
#include "transactiontablemodel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setBaseSize(300,200);
    setCentralWidget(mdiArea);

    clientTableModel=0;
    transactionTableModel=0;
    accountTableModel=0;
    datalistwidget=0;

    setupMenu();
    setupModels();

    setWindowTitle(trUtf8("Bank adatbázis"));
    setMaximumHeight(360);
    setMaximumWidth(520);

}

MainWindow::~MainWindow(){

    delete datalistwidget;
    delete clientTableModel;
    delete transactionTableModel;
    delete accountTableModel;

}

void MainWindow::closeEvent(QCloseEvent *event){

    mdiArea->closeAllSubWindows();

}


void MainWindow::viewClients_Triggered(){

    mdiArea->closeAllSubWindows();

    datalistwidget = new DataListWidget(this);
    datalistwidget->setModel(clientTableModel, accountTableModel, transactionTableModel, client);
    mdiArea->addSubWindow(datalistwidget);
    datalistwidget->show();

}

void MainWindow::viewAccounts_Triggered(){

    mdiArea->closeAllSubWindows();

    datalistwidget = new DataListWidget(this);
    datalistwidget->setModel(clientTableModel, accountTableModel, transactionTableModel, account);
    mdiArea->addSubWindow(datalistwidget);
    datalistwidget->show();

}

void MainWindow::viewTransactions_Triggered(){

    mdiArea->closeAllSubWindows();

    datalistwidget = new DataListWidget(this);
    datalistwidget->setModel(clientTableModel, accountTableModel, transactionTableModel, transaction);
    mdiArea->addSubWindow(datalistwidget);
    datalistwidget->show();
    connect(datalistwidget, SIGNAL(updateAccounts(int,int,int)), accountTableModel, SLOT(addTransaction(int,int,int)));

}

void MainWindow::addTransaction_Triggered(){

    mdiArea->closeAllSubWindows();

    manageaccountwidget = new ManageAccountWidget(this);
    manageaccountwidget->setModel(accountTableModel, transactionTableModel);

    connect(manageaccountwidget->transactiondialog, SIGNAL(updateAccounts(int,int,int)), accountTableModel, SLOT(addTransaction(int,int,int)));

    mdiArea->addSubWindow(manageaccountwidget);
    manageaccountwidget->show();

}

void MainWindow::blockAccount_Triggered(){

    mdiArea->closeAllSubWindows();

    blockaccountwidget = new BlockAccountWidget(this);
    blockaccountwidget->setModel(accountTableModel);

    mdiArea->addSubWindow(blockaccountwidget);
    blockaccountwidget->show();

}

void MainWindow::updateAccountsTable(int source, int target, int amount){

    accountTableModel->addTransaction(source,target,amount);

}


void MainWindow::setupMenu(){

    viewMenu = menuBar()->addMenu(trUtf8("&Adatok megtekintése"));

    viewClients = new QAction(trUtf8("Ügyfelek megtekintése"), this);
    viewClients->setStatusTip(trUtf8("A rendszerben lévő ügyfelek kilistázása."));
    connect(viewClients, SIGNAL(triggered()), this, SLOT(viewClients_Triggered()));
    viewMenu->addAction(viewClients);

    viewAccounts = new QAction(trUtf8("Számlák megtekintése"), this);
    viewAccounts->setStatusTip(trUtf8("A rendszerben lévő számlák kilistázása."));
    connect(viewAccounts, SIGNAL(triggered()), this, SLOT(viewAccounts_Triggered()));
    viewMenu->addAction(viewAccounts);

    viewTransactions = new QAction(trUtf8("Utalások megtekintése"), this);
    viewTransactions->setStatusTip(trUtf8("A rendszerben lévő utalások kilistázása."));
    connect(viewTransactions, SIGNAL(triggered()), this, SLOT(viewTransactions_Triggered()));
    viewMenu->addAction(viewTransactions);


    actionMenu = menuBar()->addMenu(trUtf8("&Adatok kezelése"));

    addTransaction = new QAction(trUtf8("Új utalás"), this);
    connect(addTransaction, SIGNAL(triggered()), this, SLOT(addTransaction_Triggered()));
    actionMenu->addAction(addTransaction);

    blockAccount = new QAction(trUtf8("Számla blokkolása/feloldása"), this);
    connect(blockAccount, SIGNAL(triggered()), this, SLOT(blockAccount_Triggered()));
    actionMenu->addAction(blockAccount);

}

void MainWindow::setupModels(){

    clientTableModel = new ClientTableModel();
    clientTableModel->select();

    transactionTableModel = new TransactionTableModel();
    transactionTableModel->select();

    accountTableModel = new AccountTableModel(transactionTableModel);
    accountTableModel->select();

}
