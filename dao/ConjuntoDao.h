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

    // retorna todos os conjuntos cadastrados
    QList<ConjuntoModel*> getAll();
    ConjuntoModel* getById(int id);
    QList<ConjuntoModel*> getConjuntosByRoupa(int idRoupa);
    // insere um novo conjunto no banco
    bool insert(ConjuntoModel* conjunto);
    // atualiza um conjunto existente no banco
    bool update(ConjuntoModel* conjunto);
    bool remove(int id);
    QList<QString> verificarEstoqueBaixo();
};

#endif // CONJUNTODAO_H