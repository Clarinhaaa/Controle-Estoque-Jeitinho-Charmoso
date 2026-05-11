#include "RoupaConjuntoModel.h"
#include "TecidoModel.h"
#include "TecidoDao.h"

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

void RoupaConjuntoModel::aumentarEstoque(int qtd) {}

void RoupaConjuntoModel::diminuirEstoque(int qtd) {}