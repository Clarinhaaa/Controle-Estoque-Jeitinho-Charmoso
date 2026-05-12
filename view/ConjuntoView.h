#ifndef CONJUNTOVIEW_H
#define CONJUNTOVIEW_H

#include <QTextStream>
#include "Pagina.h"
#include "model/ConjuntoModel.h"
#include "dao/ConjuntoDao.h"

class ConjuntoView : public Pagina
{
public:
    ConjuntoView() : Pagina() {}
    ~ConjuntoView() {}

    void load();

private:
    QList<ConjuntoModel*> listaConjuntos;
    ConjuntoDao conDao;

    void form(bool isEdicao);
    ConjuntoModel* validarId();
    void gerenciarEstoque();
    void remover();
};

#endif // CONJUNTOVIEW_H
