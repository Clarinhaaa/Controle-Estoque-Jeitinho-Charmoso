#ifndef TECIDOVIEW_H
#define TECIDOVIEW_H

#include <QTextStream>
#include "Pagina.h"
#include "model/TecidoModel.h"
#include "dao/TecidoDao.h"

class TecidoView : public Pagina
{
public:
    TecidoView() : Pagina() {}
    ~TecidoView() {}

    void load();

private:
    QList<TecidoModel*> listaTecidos;
    TecidoDao teciDao;

    // responsável pelo cadastro e edição
    void form(bool isEdicao);
    // verifica se o ID inserido pelo usuário existe no banco
    TecidoModel* validarId();
    // form de edição de estoque
    void gerenciarEstoque();

    // remove um tecido pelo id
    // metodo adicionado para implementar o RF018 - remocao de tecidos
    void remover();
};

#endif // TECIDOVIEW_H