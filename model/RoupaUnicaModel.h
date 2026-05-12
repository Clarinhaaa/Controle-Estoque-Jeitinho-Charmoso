#ifndef ROUPAUNICAMODEL_H
#define ROUPAUNICAMODEL_H

#include "model/RoupaModel.h"

class RoupaUnicaModel : public RoupaModel
{
public:
    RoupaUnicaModel() : RoupaModel() {}
    RoupaUnicaModel(int id, const QString &nome, const QString &tipo, const QString &tamanho,
                    int estoque, float custo, int idTecido, float preco)
        : RoupaModel(id, nome, tipo, tamanho, estoque, custo, idTecido) {
        this->preco = preco;
    }
    ~RoupaUnicaModel() {};

    float getPreco() { return this->preco; }
    void setPreco(float preco) { this->preco = preco; }

    QString toString();

    void aumentarEstoque(int qtd);
    void diminuirEstoque(int qtd);

    float calcularPreco(float custoRoupa, float custoTecido);

private:
    float preco;
};

#endif // ROUPAUNICAMODEL_H
