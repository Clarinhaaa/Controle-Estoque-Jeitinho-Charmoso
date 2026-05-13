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

RoupaModel* RoupaDao::getById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Roupa WHERE id_roupa = :id;");
    query.bindValue(":id", id);

    RoupaModel* roupa = nullptr;
    if (query.exec()) {
        if (query.next()) {
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
        }
    }

    return roupa;
}

QList<RoupaConjuntoModel*> RoupaDao::getRoupasByConjunto(int idConjunto) {
    // busca roupas relacionadas ao conjunto a partir da tabela Conjunto_has_Roupa
    QSqlQuery query;
    query.prepare("SELECT r.id_roupa FROM Roupa r, Conjunto_has_Roupa cr WHERE r.id_roupa = cr.id_roupa_conjunto AND cr.id_conjunto_roupa = :id");
    query.bindValue(":id", idConjunto);

    QList<RoupaConjuntoModel*> lista;
    if (query.exec()) {
        while (query.next()) {
            int idRoupa = query.value(0).toInt();
            RoupaConjuntoModel* r = static_cast<RoupaConjuntoModel*>(this->getById(idRoupa));
            lista.append(r);
        }
    }

    return lista;
}

// busca o ID e estoque de roupas com estoque <= 5 e armazena os dados numa lista
QList<QString> RoupaDao::verificarEstoqueBaixo() {
    QSqlQuery query;
    query.prepare("SELECT id_roupa, nome_roupa, estoque_roupa FROM Roupa WHERE estoque_roupa <= 5;");

    QList<QString> listaEstoqueBaixo;
    if (query.exec()) {
        while (query.next()) {
            QString id = query.value("id_roupa").toString();
            QString nome = query.value("nome_roupa").toString();
            QString qtd = query.value("estoque_roupa").toString();
            listaEstoqueBaixo.append(QString("%1 - %2 com %3 itens!").arg(id, nome, qtd));
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