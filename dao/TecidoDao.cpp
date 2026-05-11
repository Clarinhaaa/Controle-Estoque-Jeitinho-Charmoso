#include "TecidoDao.h"
#include <QSqlError>

// Busca todos os tecidos cadastrados
QList<TecidoModel*> TecidoDao::getAll()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Tecido;");

    QList<TecidoModel*> listTecido;

    query.exec();
    while (query.next()) {
        TecidoModel* tecido = new TecidoModel();
        tecido->setId(query.value(0).toInt());
        tecido->setEstampa(query.value(1).toString());
        tecido->setMaterial(query.value(2).toString());
        tecido->setMetros(query.value(3).toFloat());
        tecido->setCusto(query.value(4).toFloat());
        listTecido.append(tecido);
    }

    return listTecido;
}

QList<TecidoModel*> TecidoDao::getAllAvailable()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Tecido WHERE metros_tecido > 0;");

    QList<TecidoModel*> listTecido;

    query.exec();
    while (query.next()) {
        TecidoModel* tecido = new TecidoModel();
        tecido->setId(query.value(0).toInt());
        tecido->setEstampa(query.value(1).toString());
        tecido->setMaterial(query.value(2).toString());
        tecido->setMetros(query.value(3).toFloat());
        tecido->setCusto(query.value(4).toFloat());

        listTecido.append(tecido);
    }

    return listTecido;
}

// Busca um tecido pelo ID
TecidoModel* TecidoDao::getById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Tecido WHERE id_tecido = :id;");
    query.bindValue(":id", id);

    TecidoModel* tecido = nullptr;
    if (query.exec()) {
        if (query.next()) {
            tecido = new TecidoModel();
            tecido->setId(id);
            tecido->setEstampa(query.value(1).toString());
            tecido->setMaterial(query.value(2).toString());
            tecido->setMetros(query.value(3).toFloat());
            tecido->setCusto(query.value(4).toFloat());
        }
    }

    return tecido;
}

// Busca todos os valores de uma coluna
QList<TecidoModel*> TecidoDao::getByColumn(const QString& coluna, QVariant valor) {
    QSqlQuery query;
    if (coluna == "estampa_tecido") {
        query.prepare(QString("SELECT * FROM Tecido WHERE %1 LIKE :valor;").arg(coluna));
        query.bindValue(":valor", QString("%%1%").arg(valor.toString()));
    } else {
        if (coluna == "material_tecido") {
            query.prepare(QString("SELECT * FROM Tecido WHERE %1 = :valor;").arg(coluna));
        } else { // coluna == "metros_tecido" OU "custo_tecido"
            query.prepare(QString("SELECT * FROM Tecido WHERE %1 >= :valor;").arg(coluna));
        }
        query.bindValue(":valor", valor);
    }

    QList<TecidoModel*> listTecido;

    query.exec();
    while (query.next()) {
        TecidoModel* tecido = new TecidoModel();
        tecido->setId(query.value(0).toInt());
        tecido->setEstampa(query.value(1).toString());
        tecido->setMaterial(query.value(2).toString());
        tecido->setMetros(query.value(3).toFloat());
        tecido->setCusto(query.value(4).toFloat());

        listTecido.append(tecido);
        delete tecido;
    }

    return listTecido;
}

// Insere um tecido novo
bool TecidoDao::insert(TecidoModel* tecido)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Tecido(estampa_tecido, material_tecido, metros_tecido, custo_tecido)"
                  "VALUES (:estampa, :material, :metros, :custo);");
    query.bindValue(":estampa", tecido->getEstampa());
    query.bindValue(":material", tecido->getMaterial());
    query.bindValue(":metros", tecido->getMetros());
    query.bindValue(":custo", tecido->getCusto());
    bool exec = query.exec();

    return (exec) ? true : false;
}

bool TecidoDao::update(TecidoModel* tecido)
{
    bool exec = false;
    if (tecido != nullptr) {
        QSqlQuery query;
        query.prepare("UPDATE Tecido SET estampa_tecido = :estampa, material_tecido = :material, metros_tecido = :metros, custo_tecido = :custo WHERE id_tecido = :id;");
        query.bindValue(":id", tecido->getId());
        query.bindValue(":estampa", tecido->getEstampa());
        query.bindValue(":material", tecido->getMaterial());
        query.bindValue(":metros", tecido->getMetros());
        query.bindValue(":custo", tecido->getCusto());
        exec = query.exec();
    }

    return (exec) ? true : false;
}