#include "ConjuntoModel.h"

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

    for (RoupaConjuntoModel* rc : roupas) {
        str += rc->toString();
    }

    return str;
}

void ConjuntoModel::aumentarEstoque(int qtd) {}

void ConjuntoModel::diminuirEstoque(int qtd) {}