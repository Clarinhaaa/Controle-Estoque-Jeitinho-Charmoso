#ifndef CONJUNTODAO_H
#define CONJUNTODAO_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class ConjuntoDao
{
public:
    ConjuntoDao();
    int insert(QString nome); // Retorna o ID do conjunto gerado
    bool vincularPecas(int idConjunto, QList<int> idsPecas);
};

#endif // CONJUNTODAO_H
