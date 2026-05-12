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

    QList<TecidoModel*> getAll();
    QList<TecidoModel*> getAllAvailable();
    TecidoModel* getById(int id);
    QList<TecidoModel*> getByColumn(const QString& coluna, QVariant valor);

    bool insert(TecidoModel* tecido);

    bool update(TecidoModel* tecido);
};

#endif // TECIDODAO_H
