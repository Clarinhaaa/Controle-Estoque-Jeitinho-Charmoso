#ifndef ROUPADAO_H
#define ROUPADAO_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include "model/RoupaModel.h"

class RoupaDao {
public:
    RoupaDao() {}
    ~RoupaDao() {}

    QList<RoupaModel*> getAll();
    QList<RoupaModel*> getRoupasByConjunto();

    QList<QString> verificarEstoqueBaixo();
    bool remove(int id);
};

#endif