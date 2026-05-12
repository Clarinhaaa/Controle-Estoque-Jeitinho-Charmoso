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
    // retorna um conjunto pelo ID, ou nullptr se não encontrar
    ConjuntoModel* getById(int id);
    // insere um novo conjunto no banco
    bool insert(ConjuntoModel* conjunto);
    // atualiza um conjunto existente no banco
    bool update(ConjuntoModel* conjunto);
};

#endif // CONJUNTODAO_H