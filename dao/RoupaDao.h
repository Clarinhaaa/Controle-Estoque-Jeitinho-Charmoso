#ifndef ROUPADAO_H
#define ROUPADAO_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include "model/RoupaModel.h"
#include "RoupaConjuntoModel.h"

class RoupaDao {
public:
    RoupaDao() {}
    ~RoupaDao() {}

    QList<RoupaModel*> getAll();
    QList<RoupaConjuntoModel*> getAllConjunto();
    RoupaModel* getById(int id);
    // retorna lista de roupas ligadas a um conjunto
    QList<RoupaConjuntoModel*> getRoupasByConjunto(int idConjunto);

    QList<QString> verificarEstoqueBaixo();
    bool remove(int id);
};

#endif