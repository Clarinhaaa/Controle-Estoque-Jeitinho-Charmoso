#include "ConjuntoDao.h"
#include "RoupaDao.h"

QList<ConjuntoModel*> ConjuntoDao::getAll()
{
    RoupaDao rDao;
    QSqlQuery query;
    query.prepare("SELECT * FROM Conjunto;");

    QList<ConjuntoModel*> listConjunto;

    query.exec();
    while (query.next()) {
        ConjuntoModel* conjunto = new ConjuntoModel();
        conjunto->setId(query.value(0).toInt());
        conjunto->setNome(query.value(1).toString());
        conjunto->setEstoque(query.value(2).toInt());
        conjunto->setPreco(query.value(3).toFloat());
        QList<RoupaConjuntoModel*> roupas = rDao.getRoupasByConjunto(conjunto->getId());
        conjunto->setRoupas(roupas);

        listConjunto.append(conjunto);
    }

    return listConjunto;
}

ConjuntoModel* ConjuntoDao::getById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Conjunto WHERE id_conjunto = :id;");
    query.bindValue(":id", id);

    ConjuntoModel* conjunto = nullptr;
    if (query.exec()) {
        if (query.next()) {
            conjunto = new ConjuntoModel();
            conjunto->setId(id);
            conjunto->setNome(query.value(1).toString());
            conjunto->setEstoque(query.value(2).toInt());
            conjunto->setPreco(query.value(3).toFloat());
        }
    }

    return conjunto;
}

bool ConjuntoDao::remove(int id) {
    QSqlQuery queryCon;
    queryCon.prepare("DELETE FROM Conjunto WHERE id_conjunto = :id");
    queryCon.bindValue(":id", id);

    // desvincula o conjunto das roupas, deletando os registros na tabela Conjunto_has_Roupa
    QSqlQuery queryConHasRoupa;
    queryConHasRoupa.prepare("DELETE FROM Conjunto_Has_Roupa WHERE id_conjunto_roupa = :id");
    queryConHasRoupa.bindValue(":id", id);

    bool exec = queryCon.exec() && queryConHasRoupa.exec();

    return (exec) ? true : false;
}