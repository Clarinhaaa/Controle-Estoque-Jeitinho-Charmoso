#include "dao/RoupaDao.h"
#include <QSqlQuery>
#include <QSqlError>
#include "model/RoupaConjuntoModel.h"
#include "model/RoupaUnicaModel.h"

// busca todas as roupas cadastradas
QList<RoupaModel*> RoupaDao::getAll()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Roupa;");

    QList<RoupaModel*> listRoupa;

    query.exec();
    while (query.next()) {
        RoupaModel* roupa = nullptr;
        float preco = query.value(6).toFloat();

        // verifica o tipo de "roupa"
        if (preco < 0) {
            RoupaConjuntoModel* rc = new RoupaConjuntoModel();
            roupa = rc;
        } else {
            RoupaUnicaModel* ru = new RoupaUnicaModel();
            ru->setPreco(preco);
            roupa = ru;
        }

        roupa->setId(query.value(0).toInt());
        roupa->setNome(query.value(1).toString());
        roupa->setTipo(query.value(2).toString());
        roupa->setTamanho(query.value(3).toString());
        roupa->setEstoque(query.value(4).toInt());
        roupa->setCusto(query.value(5).toFloat());
        // setPreco() definido acima
        roupa->setIdTecido(query.value(7).toInt());
        listRoupa.append(roupa);
    }

    return listRoupa;
}

QList<RoupaModel*> RoupaDao::getRoupasByConjunto() {
    // busca roupas relacionadas ao conjunto a partir da tabela Conjunto_has_Roupa
}

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