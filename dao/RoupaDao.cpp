#include "RoupaDao.h"

RoupaDao::RoupaDao() {}

QList<RoupaModel> RoupaDao::filtrarRoupas(QString nome, QString tipo, QString tamanho,
                                          double precoMax, int estoqueMin,
                                          QString tecido, int conjunto) {
    QList<RoupaModel> lista;
    QSqlQuery query;
    QString sql = "SELECT * FROM Roupa WHERE 1=1";

    if (!nome.isEmpty())    sql += " AND nome_roupa LIKE :nome";
    if (!tipo.isEmpty())    sql += " AND tipo_roupa = :tipo";
    if (!tamanho.isEmpty()) sql += " AND tamanho_roupa = :tamanho";
    if (precoMax > 0)       sql += " AND preco_roupa <= :preco";
    if (estoqueMin >= 0)    sql += " AND estoque_roupa >= :estoque";
    if (!tecido.isEmpty())  sql += " AND tecido_roupa = :tecido";
    if (conjunto != -1)     sql += " AND eh_conjunto = :conjunto";

    query.prepare(sql);

    // bind seguro dos valores
    if (!nome.isEmpty())    query.bindValue(":nome", "%" + nome + "%");
    if (!tipo.isEmpty())    query.bindValue(":tipo", tipo);
    if (!tamanho.isEmpty()) query.bindValue(":tamanho", tamanho);
    if (precoMax > 0)       query.bindValue(":preco", precoMax);
    if (estoqueMin >= 0)    query.bindValue(":estoque", estoqueMin);
    if (!tecido.isEmpty())  query.bindValue(":tecido", tecido);
    if (conjunto != -1)     query.bindValue(":conjunto", conjunto);

    if (query.exec()) {
        while (query.next()) {
            RoupaModel r;
            r.setId(query.value("id_roupa").toInt());
            r.setNome(query.value("nome_roupa").toString());
            r.setTipo(query.value("tipo_roupa").toString());
            r.setTamanho(query.value("tamanho_roupa").toString());
            r.setPreco(query.value("preco_roupa").toDouble());
            r.setEstoque(query.value("estoque_roupa").toInt());
            r.setTecido(query.value("tecido_roupa").toString());
            r.setConjunto(query.value("eh_conjunto").toInt());
            lista.append(r);
        }
    }
    return lista;
}