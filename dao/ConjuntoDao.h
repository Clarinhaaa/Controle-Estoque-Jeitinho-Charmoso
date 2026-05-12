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
};

#endif // CONJUNTODAO_H
