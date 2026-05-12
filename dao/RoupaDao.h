#ifndef ROUPADAO_H
#define ROUPADAO_H

#include <QtSql>
#include "model/RoupaModel.h"

class RoupaDao {
public:
    RoupaDao();


    void verificarEstoqueBaixo();   // RF022
    bool removerRoupa(int id);      // RF005
};

#endif