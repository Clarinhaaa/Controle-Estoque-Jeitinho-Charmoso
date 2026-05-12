#include "conjuntodao.h"

ConjuntoDao::ConjuntoDao() {}

int ConjuntoDao::insert(QString nome) {
    QSqlQuery query;
    query.prepare("INSERT INTO Conjunto (nome_conjunto) VALUES (:nome)");
    query.bindValue(":nome", nome);

    if (query.exec()) {
        return query.lastInsertId().toInt();
    }
    qDebug() << "Erro ao inserir Conjunto:" << query.lastError().text();
    return -1;
}

bool ConjuntoDao::vincularPecas(int idConjunto, QList<int> idsPecas) {
    QSqlQuery query;
    bool sucesso = true;

    for (int idPeca : idsPecas) {
        query.prepare("UPDATE Roupa SET id_conjunto = :idConj WHERE id_roupa = :idPeca");
        query.bindValue(":idConj", idConjunto);
        query.bindValue(":idPeca", idPeca);

        if (!query.exec()) {
            qDebug() << "Erro ao vincular peca" << idPeca << ":" << query.lastError().text();
            sucesso = false;
        }
    }
    return sucesso;
}