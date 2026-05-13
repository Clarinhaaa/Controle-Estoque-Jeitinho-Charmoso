#include "model/RoupaModel.h"

RoupaModel::RoupaModel(int id, const QString &nome, const QString &tipo, const QString &tamanho, int estoque, float custo, int idTecido) {
    this->id = id;
    this->nome = nome;
    this->tipo = tipo;
    this->tamanho = tamanho;
    this->estoque = estoque;
    this->custo = custo;
    this->idTecido = idTecido;
}

QString RoupaModel::toString() {
    QString custoFormatado = QString::number(custo, 'f', 2);

    QString str = QString("ID: %1\n%2 %3 - %4\nEstoque: %5\nCusto: R$%6\n")
    .arg(QString::number(id), tipo, nome, tamanho, QString::number(estoque), custoFormatado);

    return str;
}