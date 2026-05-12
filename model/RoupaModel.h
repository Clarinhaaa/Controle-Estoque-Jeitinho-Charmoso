#ifndef ROUPAMODEL_H
#define ROUPAMODEL_H

#include <QString>

class RoupaModel
{
private:
    int id;
    QString nome;
    QString tipo;
    QString tamanho;
    int estoque;
    float custo;

public:
    RoupaModel();
    virtual ~RoupaModel() {}

    int getId() const;
    void setId(int newId);

    QString getNome() const;
    void setNome(const QString &newNome);

    QString getTipo() const;
    void setTipo(const QString &newTipo);

    QString getTamanho() const;
    void setTamanho(const QString &newTamanho);

    int getEstoque() const;
    void setEstoque(int newEstoque);

    float getCusto() const;
    void setCusto(float newCusto);

};

#endif // ROUPAMODEL_H
