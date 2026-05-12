#ifndef ROUPAUNICAMODEL_H
#define ROUPAUNICAMODEL_H

#include "model/RoupaModel.h"

class RoupaUnicaModel : public RoupaModel
{
public:
    RoupaUnicaModel() : RoupaModel() {}
    RoupaUnicaModel(int id, const QString &nome, const QString &tipo, const QString &tamanho,
                    const QString &fornecedor, int estoque, float custo, int idTecido, float preco)
        : RoupaModel(id, nome, tipo, tamanho, fornecedor, estoque, custo, idTecido) {
        this->preco = preco;
    }
    ~RoupaUnicaModel() {};

    QString toString();

    void aumentarEstoque(int qtd);
    void diminuirEstoque(int qtd);

    float calcularPreco(float custoRoupa, float custoTecido);

private:
    float preco;
};

#endif // ROUPAUNICAMODEL_H
