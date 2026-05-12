#ifndef ROUPAVIEW_H
#define ROUPAVIEW_H

#include <QTextStream>
#include "Pagina.h"
#include "model/RoupaModel.h"
#include "dao/RoupaDao.h"

class RoupaView : public Pagina
{
public:
    RoupaView() : Pagina() {}
    ~RoupaView() {}

    void load();

private:
    QList<RoupaModel*> listaRoupas;
    RoupaDao rDao;

    void form(bool isEdicao, bool isUnica);
    RoupaModel* validarId();
    void gerenciarEstoque();
    void remover();
};

#endif // ROUPAVIEW_H
