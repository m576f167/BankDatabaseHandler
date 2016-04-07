#ifndef LOGINDIALOG
#define LOGINDIALOG

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include "mainwindow.h"

class LoginDialog : public QDialog{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void login();

private:
    MainWindow* mainWindow;

    QPushButton* okButton;
    QPushButton* cancelButton;
    QLineEdit* userNameEdit;
    QLineEdit* userPasswordEdit;
};

#endif // LOGINDIALOG

