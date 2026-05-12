#ifndef CONJUNTODAO_H
#define CONJUNTODAO_H

#include <QSqlQuery>
#include <QSqlRecord>
#include "model/ConjuntoModel.h"

class ConjuntoDao
{
public:
    ConjuntoDao() {}
    ~ConjuntoDao() {}

    QList<ConjuntoModel*> getAll();
    ConjuntoModel* getById(int id);
    QList<ConjuntoModel*> getConjuntosByRoupa(int idRoupa);

    bool remove(int id);
    QList<QString> verificarEstoqueBaixo();
};

#endif // CONJUNTODAO_H
