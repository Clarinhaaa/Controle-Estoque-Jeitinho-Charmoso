#ifndef PAGINAINICIAL_H
#define PAGINAINICIAL_H

#include <QString>
#include <QTextStream>
#include "Pagina.h"

class PaginaInicial : public Pagina
{
public:
    PaginaInicial() : Pagina() {};
    ~PaginaInicial() {};
    void load();
};

#endif // PAGINAINICIAL_H
