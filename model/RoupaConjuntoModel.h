#ifndef ROUPACONJUNTOMODEL_H
#define ROUPACONJUNTOMODEL_H

#include "model/RoupaModel.h"

class RoupaConjuntoModel : public RoupaModel
{
public:
    RoupaConjuntoModel() : RoupaModel() {};
    RoupaConjuntoModel(int id, const QString &nome, const QString &tipo, const QString &tamanho,
                    const QString &fornecedor, int estoque, float custo, int idTecido)
        : RoupaModel(id, nome, tipo, tamanho, fornecedor, estoque, custo, idTecido) {}
    ~RoupaConjuntoModel() {};

    QString toString();

    void aumentarEstoque(int qtd);
    void diminuirEstoque(int qtd);
};

#endif // ROUPACONJUNTOMODEL_H
