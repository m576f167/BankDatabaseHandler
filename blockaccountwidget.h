#ifndef BLOCKACCOUNTWIDGET_H
#define BLOCKACCOUNTWIDGET_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class BlockAccountWidget;
}

class BlockAccountWidget : public QWidget{
    Q_OBJECT

public:

    explicit BlockAccountWidget(QWidget *parent = 0);
    ~BlockAccountWidget();

    void setModel(QSqlTableModel* accountModel);

private slots:

    void changeAccount(const QModelIndex& index);

private:

    void setupGui();

    QSqlTableModel* accountTableModel;

    Ui::BlockAccountWidget *ui;
};

#endif // BLOCKACCOUNTWIDGET_H
