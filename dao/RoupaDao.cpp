#include "RoupaDao.h"
#include "RoupaUnicaModel.h"
#include "RoupaConjuntoModel.h"
#include <QSqlQuery>
#include <QVariant>

RoupaDao::RoupaDao() {}

QList<RoupaModel*> RoupaDao::getAll() {
    QList<RoupaModel*> lista;
    QSqlQuery query("SELECT * FROM Roupa");

    while (query.next()) {
        QString tipo = query.value("tipo_roupa").toString();
        RoupaModel* roupa = nullptr;


        if (tipo == "Conjunto") {
            RoupaConjuntoModel* conjunto = new RoupaConjuntoModel();
            conjunto->setIdConjunto(query.value("id_conjunto").toInt());
            roupa = conjunto;
        } else {
            roupa = new RoupaUnicaModel();
        }

        roupa->setId(query.value("id_roupa").toInt());
        roupa->setNome(query.value("nome_roupa").toString());
        roupa->setTipo(tipo);
        roupa->setTamanho(query.value("tamanho_roupa").toString());
        roupa->setEstoque(query.value("estoque_roupa").toInt());
        roupa->setCusto(query.value("custo_roupa").toFloat());

        lista.append(roupa);
    }
    return lista;
}
