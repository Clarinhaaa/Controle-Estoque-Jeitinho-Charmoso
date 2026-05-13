#ifndef CONJUNTOVIEW_H
#define CONJUNTOVIEW_H

#include <QTextStream>
#include "Pagina.h"
#include "model/ConjuntoModel.h"
#include "model/RoupaConjuntoModel.h"
#include "dao/ConjuntoDao.h"

class ConjuntoView : public Pagina
{
public:
    ConjuntoView() : Pagina() {}
    ~ConjuntoView() {}

    void load();

private:
    QList<ConjuntoModel*> listaConjuntos;
    QList<RoupaConjuntoModel*> listaRoupasConj;
    ConjuntoDao conDao;

    void form(bool isEdicao);
    // pede um ID ao usuário e retorna o conjunto correspondente do banco
    ConjuntoModel* validarId();
    void gerenciarEstoque();
    void remover();
};

#endif // CONJUNTOVIEW_H