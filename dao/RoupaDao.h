#ifndef ROUPADAO_H
#define ROUPADAO_H

#include <QList>
#include <QString>
#include <QtSql>
#include "../model/RoupaModel.h"

class RoupaDao {
public:
    RoupaDao();


    QList<RoupaModel> filtrarRoupas(QString nome = "", QString tipo = "",
                                    QString tamanho = "", double precoMax = 0.0,
                                    int estoqueMin = -1, QString tecido = "",
                                    int conjunto = -1);
};

#endif