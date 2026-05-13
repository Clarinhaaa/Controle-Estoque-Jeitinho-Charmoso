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

bool ConjuntoDao::insert(ConjuntoModel* conjunto)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Conjunto (nome_conjunto, estoque_conjunto, preco_conjunto)"
                  "VALUES (:nome, :estoque, :preco);");
    query.bindValue(":nome", conjunto->getNome());
    query.bindValue(":estoque", conjunto->getEstoque());
    query.bindValue(":preco", conjunto->getPreco());
  
    bool exec = query.exec()

    return (exec) ? true : false;
}

// atualiza um conjunto existente no banco pelo ID
bool ConjuntoDao::update(ConjuntoModel* conjunto)
{
    QSqlQuery query;
    query.prepare("UPDATE Conjunto SET nome_conjunto = :nome, estoque_conjunto = :estoque, preco_conjunto = :preco WHERE id_conjunto = :id;");
    query.bindValue(":nome", conjunto->getNome());
    query.bindValue(":estoque", conjunto->getEstoque());
    query.bindValue(":preco", conjunto->getPreco());
    query.bindValue(":id", conjunto->getId());

    bool exec = query.exec()

    return (exec) ? true : false;

QList<ConjuntoModel*> ConjuntoDao::getConjuntosByRoupa(int idRoupa) {
    // busca roupas relacionadas ao conjunto a partir da tabela Conjunto_has_Roupa
    QSqlQuery query;
    query.prepare("SELECT c.id_conjunto FROM Conjunto c, Conjunto_has_Roupa cr WHERE c.id_conjunto = cr.id_conjunto_roupa AND cr.id_roupa_conjunto = :id");
    query.bindValue(":id", idRoupa);

    QList<ConjuntoModel*> lista;
    if (query.exec()) {
        while (query.next()) {
            int idConjunto = query.value(0).toInt();
            ConjuntoModel* r = this->getById(idConjunto);
            lista.append(r);
        }
    }

    return lista;
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

QList<QString> ConjuntoDao::verificarEstoqueBaixo() {
    QSqlQuery query;
    query.prepare("SELECT id_conjunto, nome_conjunto, estoque_conjunto FROM Conjunto WHERE estoque_conjunto <= 5;");

    QList<QString> listaEstoqueBaixo;
    if (query.exec()) {
        while (query.next()) {
            QString id = query.value("id_conjunto").toString();
            QString nome = query.value("nome_conjunto").toString();
            QString qtd = query.value("estoque_conjunto").toString();
            listaEstoqueBaixo.append(QString("%1 - %2 com %3 itens!").arg(id, nome, qtd));
        } // caso o loop não ocorra, a lista é retornada vazia
    }
    return listaEstoqueBaixo;
}