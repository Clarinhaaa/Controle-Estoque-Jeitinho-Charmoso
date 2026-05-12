#ifndef ROUPADAO_H
#define ROUPADAO_H

#include <QList>
#include "RoupaModel.h"

class RoupaDao
{
public:
    RoupaDao();
    QList<RoupaModel*> getAll();
};

#endif // ROUPADAO_H
