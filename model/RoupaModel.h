#ifndef ROUPAMODEL_H
#define ROUPAMODEL_H

#include <QString>
#include <QStringList>

class RoupaModel {
public:
    // Construtores
    RoupaModel() {}
    RoupaModel(int id, const QString &nome, const QString &tipo, const QString &tamanho, const QString &fornecedor, int estoque, float custo, int idTecido);
    virtual ~RoupaModel() {}

    // RF013: Listas para o dropdown
    static inline const QStringList OPCOES_TIPO = {"Camisa", "Short", "Vestido"};
    static inline const QStringList OPCOES_TAMANHO = {"P", "M", "G", "GG", "Único"};

    QString toString();
    virtual void aumentarEstoque(int qtd) = 0;
    virtual void diminuirEstoque(int qtd) = 0;

    int getId() const { return id; }
    QString getNome() const { return nome; }
    QString getTipo() const { return tipo; }
    QString getTamanho() const { return tamanho; }

protected:
    int id;
    QString nome;
    QString tipo;
    QString tamanho;
    QString fornecedor;
    int estoque;
    float custo;
    int idTecido;
};

#endif