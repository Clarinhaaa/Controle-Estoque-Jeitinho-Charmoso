#include "RoupaConjuntoDao.h"

RoupaConjuntoDao::RoupaConjuntoDao() {}

bool RoupaConjuntoDao::removerConjunto(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Conjunto WHERE id_conjunto = :id");
    query.bindValue(":id", id);
    return query.exec();
}
=======

