#ifndef TECIDOVIEW_H
#define TECIDOVIEW_H

#include <QTextStream>
#include "Pagina.h"
#include "TecidoModel.h"
#include "TecidoDao.h"

class TecidoView : public Pagina
{
public:
    TecidoView() : Pagina() {}
    ~TecidoView() {}
    void load();
private:
    QList<TecidoModel*> listaTecidos;
    TecidoDao teciDao;

    void form(bool isEdicao);
    void validarVazio(QString campo);
    TecidoModel* validarId();
    void retornar();
    void gerenciarEstoque();
};

#endif // TECIDOVIEW_H
