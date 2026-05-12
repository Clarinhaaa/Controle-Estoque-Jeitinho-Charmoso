#ifndef ROUPAUNICADAO_H
#define ROUPAUNICADAO_H

#include "RoupaDao.h"
#include "RoupaUnicaModel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class RoupaUnicaDao : public RoupaDao
{
public:
    RoupaUnicaDao();
    bool insert(RoupaUnicaModel &roupa);
};

#endif // ROUPAUNICADAO_H
