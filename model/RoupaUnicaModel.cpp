#include "RoupaUnicaModel.h"
#include "model/TecidoModel.h"
#include "dao/TecidoDao.h"

QString RoupaUnicaModel::toString() {
    // busca o tecido relacionado à roupa
    TecidoDao teciDao;
    TecidoModel* tecido = teciDao.getById(idTecido);

    // atualiza a roupa única com seu preço e tecido
    QString str = RoupaModel::toString();
    str += QString("Preço: R$%1\nTecido:\n").arg(preco);
    str += tecido->toString();

    return str;
}

void RoupaUnicaModel::aumentarEstoque(int qtd) {}

void RoupaUnicaModel::diminuirEstoque(int qtd) {}

// calcula o preço de acordo com a estratégia da loja
float RoupaUnicaModel::calcularPreco(float custoRoupa, float custoTecido) {
    return custoRoupa + custoTecido + 8;
}