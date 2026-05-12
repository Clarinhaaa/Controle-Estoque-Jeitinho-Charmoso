#include "TecidoModel.h"
#include <QTextStream>
#include <QIODevice>

TecidoModel::TecidoModel(int id, const QString& estampa, const QString& material, float metros, float custo) {
    this->id = id;
    this->estampa = estampa;
    this->material = material;
    this->metros = metros;
    this->custo = custo;
}

QString TecidoModel::toString() {
    QString metrosFormatado = QString::number(metros, 'f', 2);
    QString custoFormatado = QString::number(custo, 'f', 2);
    return QString("ID: %1\nEstampa: %2\nMaterial: %3\nMetros: %4\nCusto: R$%5\n"
                   ).arg(QString::number(id), estampa, material, metrosFormatado, custoFormatado);
}

void TecidoModel::aumentarEstoque(float qtd) {
    this->metros += qtd;
}

// Não permite estoque negativo. Se a quantidade for maior do que o valor atual, ele assume 0
void TecidoModel::diminuirEstoque(float qtd) {
    float resultado = this->metros - qtd;
    this->metros = (resultado < 0) ? 0 : resultado;
}