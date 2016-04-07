#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T20:26:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BankTransactionDatabase
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    clienttablemodel.cpp \
    accounttablemodel.cpp \
    transactiontablemodel.cpp \
    datalistwidget.cpp \
    manageaccountwidget.cpp \
    transactiondialog.cpp \
    blockaccountwidget.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    clienttablemodel.h \
    accounttablemodel.h \
    transactiontablemodel.h \
    datalistwidget.h \
    manageaccountwidget.h \
    transactiondialog.h \
    blockaccountwidget.h

FORMS    += \
    datalistwidget.ui \
    manageaccountwidget.ui \
    transactiondialog.ui \
    blockaccountwidget.ui

DISTFILES += \
    bankdb.sql
