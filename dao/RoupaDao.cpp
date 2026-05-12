#include "dao/RoupaDao.h"
#include <QSqlQuery>
#include <QSqlError>

// busca o ID e estoque de roupas com estoque <= 5 e armazena os dados numa lista
QList<QString> RoupaDao::verificarEstoqueBaixo() {
    QSqlQuery query;
    query.prepare("SELECT id_roupa, estoque_roupa FROM Roupa WHERE estoque_roupa <= 5");

    QList<QString> listaEstoqueBaixo;
    if (query.exec()) {
        while (query.next()) {
            QString id = query.value("id_roupa").toString();
            QString qtd = query.value("estoque_roupa").toString();
            listaEstoqueBaixo.append(QString("ID: %1 | Estoque: %2").arg(id, qtd));
        } // caso o loop não ocorra, a lista é retornada vazia
    }
    // a lógica para lidar com o resultado será em RoupaView.cpp
    return listaEstoqueBaixo;
}

// falta lógica de verificar se faz parte de um conjunto (OVERRIDE EM RoupaConjuntoDao)
bool RoupaDao::remove(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Roupa WHERE id_roupa = :id");
    query.bindValue(":id", id);

    bool exec = query.exec();

    return (exec) ? true : false;
}