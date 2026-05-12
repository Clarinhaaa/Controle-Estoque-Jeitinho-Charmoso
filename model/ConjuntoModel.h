#ifndef CONJUNTOMODEL_H
#define CONJUNTOMODEL_H

#include <QString>
#include "model/RoupaConjuntoModel.h"

class ConjuntoModel
{
public:
    ConjuntoModel() {}
    ConjuntoModel(int id, QString nome, int estoque, float preco, QList<RoupaConjuntoModel*> roupas);

    int getId() { return this->id; }
    void setId(int id) { this->id = id; }

    QString getNome() { return this->nome; }
    void setNome(QString nome) { this->nome = nome; }

    int getEstoque() { return this->estoque; }
    void setEstoque(int estoque) { this->estoque = estoque; }

    float getPreco() { return this->preco; }
    void setPreco(float preco) { this->preco = preco; }

    QList<RoupaConjuntoModel*> getRoupas() { return this->roupas; }
    void setRoupas(QList<RoupaConjuntoModel*> roupas) { this->roupas = roupas; }

    QString toString();

    void aumentarEstoque(int qtd);
    void diminuirEstoque(int qtd);
    float calcularPreco(QList<RoupaConjuntoModel*> roupas);

private:
    int id;
    QString nome;
    int estoque;
    float preco;
    QList<RoupaConjuntoModel*> roupas;
};

#endif // CONJUNTOMODEL_H
