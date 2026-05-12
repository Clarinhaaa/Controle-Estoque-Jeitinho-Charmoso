#ifndef ROUPADAO_H
#define ROUPADAO_H

#include <QString>

// deve ser abstrata, assim como RoupaModel
// assim, cada filha também tem seu próprio DAO
class RoupaDao {
public:
    RoupaDao() {}
    ~RoupaDao() {}

    QList<QString> verificarEstoqueBaixo();   // RF022
    bool remove(int id);                      // RF005

};

#endif