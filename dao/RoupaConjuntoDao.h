#ifndef ROUPACONJUNTODAO_H
#define ROUPACONJUNTODAO_H
#include <QtSql>

class RoupaConjuntoDao {
public:
    RoupaConjuntoDao();
    bool removerConjunto(int id); // A promessa do RF012
=======
#include "dao/RoupaDao.h"

class RoupaConjuntoDao : public RoupaDao
{
public:
    RoupaConjuntoDao() : RoupaDao() {};
    ~RoupaConjuntoDao() {}
};
#endif