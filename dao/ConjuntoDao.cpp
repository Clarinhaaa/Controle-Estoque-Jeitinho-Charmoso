#include "ConjuntoDao.h"

QList<ConjuntoModel*> ConjuntoDao::getAll()
{
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
        listConjunto.append(conjunto);
    }

    return listConjunto;
}