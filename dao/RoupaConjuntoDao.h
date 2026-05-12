#ifndef ROUPACONJUNTODAO_H
#define ROUPACONJUNTODAO_H

#include "RoupaDao.h"
#include "RoupaConjuntoModel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class RoupaConjuntoDao : public RoupaDao
{
public:
    RoupaConjuntoDao();
    bool insert(RoupaConjuntoModel &roupa);
};

#endif // ROUPACONJUNTODAO_H
