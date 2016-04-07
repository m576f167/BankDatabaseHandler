#include "logindialog.h"
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QSqlQueryModel>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent){

    mainWindow = 0;
    okButton = new QPushButton(trUtf8("&Ok"), this);
    cancelButton = new QPushButton(trUtf8("&Mégse"), this);
    userNameEdit = new QLineEdit();
    userPasswordEdit = new QLineEdit();
    userPasswordEdit->setEchoMode(QLineEdit::Password);

    connect(okButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    QGridLayout* inputLayout = new QGridLayout;
    inputLayout->addWidget(new QLabel(trUtf8("Felhasználónév:")), 0, 0, 1, 1);
    inputLayout->addWidget(userNameEdit, 0, 1, 1, 1);
    inputLayout->addWidget(new QLabel(trUtf8("Jelszó:")), 1, 0, 1, 1);
    inputLayout->addWidget(userPasswordEdit, 1, 1, 1, 1);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle(trUtf8("Bejelentkezés"));
    setFixedSize(300,150);

    userNameEdit->setText("gitune07");
    userPasswordEdit->setText("ultronpapa");

}

LoginDialog::~LoginDialog(){

    if (QSqlDatabase::database().isOpen()) QSqlDatabase::database().close();
    if (mainWindow != 0) delete mainWindow;

}

void LoginDialog::login(){

    if (QSqlDatabase::database().open()){

        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery("select user_id, password, name from users where user_id = '" + userNameEdit->text() + "' and password = '" + userPasswordEdit->text() + "'");

        if (model->rowCount() > 0 &&
            model->index(0, 0).data() == userNameEdit->text() &&
            model->index(0, 1).data() == userPasswordEdit->text())

        {
            QMessageBox::information(this,
                                     trUtf8("Sikeres bejelentkezés!"),
                                     trUtf8("Üdvözöljük!"));

            mainWindow = new MainWindow;
            mainWindow->show();

            delete model;

            close();
        }
        else
        {
            QMessageBox::information(this,
                                     trUtf8("Sikertelen bejelentkezés!"),
                                     trUtf8("Kérem ellenőrizze a felhasználónevet és a jelszót!"));
            delete model;
        }
    }
    else
    {
    QMessageBox::information(this,
                             trUtf8("Sikertelen bejelentkezés!"),
                             trUtf8("Az adatbázis nem elérhető!\nLépjen kapcsolatba az adminisztrátorral!"));
    }
}

