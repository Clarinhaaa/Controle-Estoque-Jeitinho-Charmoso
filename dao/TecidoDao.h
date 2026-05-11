#ifndef TECIDODAO_H
#define TECIDODAO_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include "TecidoModel.h"

class TecidoDao
{
public:
    TecidoDao() {};
    ~TecidoDao() {};

    // busca todos os tecidos cadastrados no banco
    QList<TecidoModel*> getAll();

    // busca apenas os tecidos que ainda possuem estoque disponivel
    QList<TecidoModel*> getAllAvailable();

    // busca um tecido especifico pelo id
    TecidoModel* getById(int id);

    // busca tecidos usando uma coluna especifica como filtro
    QList<TecidoModel*> getByColumn(const QString& coluna, QVariant valor);

    // cadastra um novo tecido no banco
    bool insert(TecidoModel* tecido);

    // atualiza os dados de um tecido ja cadastrado
    bool update(TecidoModel* tecido);

    // remove um tecido do banco pelo id
    // metodo adicionado para implementar o RF018 - remocao de tecidos
    bool remove(int id);
};

#endif // TECIDODAO_H