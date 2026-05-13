#include "RoupaConjuntoModel.h"
#include "model/TecidoModel.h"
#include "model/ConjuntoModel.h"
#include "dao/TecidoDao.h"
#include "dao/ConjuntoDao.h"

QString RoupaConjuntoModel::toString() {
    // Busca o tecido relacionado à roupa
    TecidoDao teciDao;
    TecidoModel* tecido = teciDao.getById(idTecido);

    // Atualiza a roupa única com seu tecido
    QString str = RoupaModel::toString();
    str += "Tecido:\n";
    str += tecido->toString();

    return str;
}

void RoupaConjuntoModel::aumentarEstoque(int qtd) {
    this->estoque += qtd;
}

void RoupaConjuntoModel::diminuirEstoque(int qtd) {
    int resultado = this->estoque - qtd;
    this->estoque = (resultado < 0) ? 0 : resultado;

    /* Se o estoque desta roupa ser menor do que o estoque atual do conjunto,
    o estoque do conjunto também é atualizado, por levar em conta o menor
    estoque de suas roupas */
    ConjuntoDao conDao;
    QList<ConjuntoModel*> lista = conDao.getConjuntosByRoupa(this->id);
    for (ConjuntoModel* con : std::as_const(lista)) {
        if (resultado < con->getEstoque())
            con->setEstoque(resultado);
    }
}