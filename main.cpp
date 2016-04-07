#include "logindialog.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("bankdb");
    db.setUserName("root");
    db.setPassword("ultron");

    LoginDialog* loginDialog = new LoginDialog();
    loginDialog->show();

    return a.exec();
}
