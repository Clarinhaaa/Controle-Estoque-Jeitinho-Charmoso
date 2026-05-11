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
    return QString("ID: %1\nEstampa: %2\nMaterial: %3\nMetros: %4\nCusto: R$%5\n"
                   ).arg(id).arg(estampa).arg(material).arg(metros, 0, 'f', 2).arg(custo, 0, 'f', 2);
}

void TecidoModel::aumentarEstoque(float qtd) {
    this->metros += qtd;
}

// Não permite estoque negativo. Se a quantidade for maior do que o valor atual, ele assume 0
void TecidoModel::diminuirEstoque(float qtd) {
    float resultado = this->metros - qtd;
    this->metros = (resultado < 0) ? 0 : resultado;
}