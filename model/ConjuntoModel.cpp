#include "ConjuntoModel.h"
#include "dao/RoupaDao.h"

ConjuntoModel::ConjuntoModel(int id, QString nome, int estoque, float preco, QList<RoupaConjuntoModel*> roupas) {
    this->id = id;
    this->nome = nome;
    this->estoque = estoque;
    this->preco = preco;
    this->roupas = roupas;
}

QString ConjuntoModel::toString() {
    QString precoFormatado = QString::number(preco, 'f', 2);

    QString str = QString("ID: %1\nNome: %2\nEstoque: %3\nPreço: R$%4\nRoupas:\n"
                          ).arg(QString::number(id), nome, QString::number(estoque), precoFormatado);

    for (RoupaConjuntoModel* rc : std::as_const(roupas)) {
        str += rc->toString();
    }

    return str;
}

void ConjuntoModel::aumentarEstoque(int qtd) {
    this->estoque += qtd;

    RoupaDao rDao;
    QList<RoupaConjuntoModel*> lista = rDao.getRoupasByConjunto(this->id);
    // Quando um conjunto aumentar o estoque, ele aumenta o estoque de todas as suas roupas
    for (RoupaConjuntoModel* r : std::as_const(lista)) {
        r->aumentarEstoque(qtd);
    }
}

void ConjuntoModel::diminuirEstoque(int qtd) {
    int resultado = this->estoque - qtd;
    this->estoque = (resultado < 0) ? 0 : resultado;

    RoupaDao rDao;
    QList<RoupaConjuntoModel*> lista = rDao.getRoupasByConjunto(this->id);
    // Quando um conjunto diminuir o estoque, ele diminui o estoque de todas as suas roupas
    for (RoupaConjuntoModel* r : std::as_const(lista)) {
        r->diminuirEstoque(qtd);
    }
}