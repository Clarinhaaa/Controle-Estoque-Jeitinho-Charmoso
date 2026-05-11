#ifndef ROUPAMODEL_H
#define ROUPAMODEL_H

#include <QString>

class RoupaModel {
private:
    int id;
    QString nome, tipo, tamanho, tecido;
    double preco;
    int estoque;
    int conjunto; // 0 para não, 1 para sim

public:
    RoupaModel();

    void setId(int v) { id = v; }
    int getId() { return id; }
    void setNome(QString v) { nome = v; }
    QString getNome() { return nome; }
    void setTipo(QString v) { tipo = v; }
    QString getTipo() { return tipo; }
    void setTamanho(QString v) { tamanho = v; }
    QString getTamanho() { return tamanho; }
    void setPreco(double v) { preco = v; }
    double getPreco() { return preco; }
    void setEstoque(int v) { estoque = v; }
    int getEstoque() { return estoque; }
    void setTecido(QString v) { tecido = v; }
    QString getTecido() { return tecido; }
    void setConjunto(int v) { conjunto = v; }
    int getConjunto() { return conjunto; }
};

#endif