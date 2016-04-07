#ifndef CLIENTTABLEMODEL_H
#define CLIENTTABLEMODEL_H

#include <QSqlRelationalTableModel>

class ClientTableModel : public QSqlRelationalTableModel{
    Q_OBJECT

public:

    ClientTableModel(QObject* parent=0);

private:

    void setupModel();

};

#endif // CLIENTTABLEMODEL_H
