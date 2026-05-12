#include "ConjuntoDao.h"

QList<ConjuntoModel*> ConjuntoDao::getAll()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Conjunto;");

    QList<ConjuntoModel*> listConjunto;

    query.exec();
    while (query.next()) {
        ConjuntoModel* conjunto = new ConjuntoModel();
        conjunto->setId(query.value("id_conjunto").toInt());
        conjunto->setNome(query.value("nome_conjunto").toString());
        conjunto->setEstoque(query.value("estoque_conjunto").toInt());
        conjunto->setPreco(query.value("preco_conjunto").toFloat());
        listConjunto.append(conjunto);
    }

    return listConjunto;
}

// busca um conjunto pelo ID no banco
ConjuntoModel* ConjuntoDao::getById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Conjunto WHERE id_conjunto = :id;");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        ConjuntoModel* conjunto = new ConjuntoModel();
        conjunto->setId(query.value("id_conjunto").toInt());
        conjunto->setNome(query.value("nome_conjunto").toString());
        conjunto->setEstoque(query.value("estoque_conjunto").toInt());
        conjunto->setPreco(query.value("preco_conjunto").toFloat());
        return conjunto;
    }

    // retorna nullptr se o ID não existir no banco
    return nullptr;
}

// insere um novo conjunto no banco
bool ConjuntoDao::insert(ConjuntoModel* conjunto)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Conjunto (nome_conjunto, estoque_conjunto, preco_conjunto) "
                  "VALUES (:nome, :estoque, :preco);");
    query.bindValue(":nome", conjunto->getNome());
    query.bindValue(":estoque", conjunto->getEstoque());
    query.bindValue(":preco", conjunto->getPreco());

    return query.exec();
}

// atualiza um conjunto existente no banco pelo ID
bool ConjuntoDao::update(ConjuntoModel* conjunto)
{
    QSqlQuery query;
    query.prepare("UPDATE Conjunto SET nome_conjunto = :nome, estoque_conjunto = :estoque, "
                  "preco_conjunto = :preco WHERE id_conjunto = :id;");
    query.bindValue(":nome", conjunto->getNome());
    query.bindValue(":estoque", conjunto->getEstoque());
    query.bindValue(":preco", conjunto->getPreco());
    query.bindValue(":id", conjunto->getId());

    return query.exec();
}