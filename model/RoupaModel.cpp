#include "model/RoupaModel.h"

RoupaModel::RoupaModel(int id, const QString &nome, const QString &tipo, const QString &tamanho, const QString &fornecedor, int estoque, float custo, int idTecido) {
    this->id = id;
    this->nome = nome;
    this->tipo = tipo;
    this->tamanho = tamanho;
    this->fornecedor = fornecedor;
    this->estoque = estoque;
    this->custo = custo;
    this->idTecido = idTecido;
}

QString RoupaModel::toString() {
    QString custoFormatado = QString::number(custo, 'f', 2);

    QString str = QString("ID: %1\n%2 %3 - %4\nFornecedor: %5\nEstoque: %6\nCusto: R$%7\n")
    .arg(QString::number(id), tipo, nome, tamanho, fornecedor, QString::number(estoque), custoFormatado);

    return str;
}