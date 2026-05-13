#ifndef ROUPAMODEL_H
#define ROUPAMODEL_H

#include <QString>
#include <QStringList>

class RoupaModel
{
public:
    RoupaModel() {}
    RoupaModel(int id, const QString &nome, const QString &tipo, const QString &tamanho, int estoque, float custo, int idTecido);
    virtual ~RoupaModel() {}

    static inline const QStringList OPCOES_TIPO = {"Camisa", "Short", "Vestido"};
    static inline const QStringList OPCOES_TAMANHO = {"2", "4", "6", "8", "10", "12", "14", "16"};

    int getId() const { return this->id; }
    void setId(int id) { this->id = id; }

    QString getNome() const { return this->nome; }
    void setNome(const QString &nome) { this->nome = nome; }

    QString getTipo() const { return this->tipo; }
    void setTipo(const QString &tipo) { this->tipo = tipo; }

    QString getTamanho() const { return this->tamanho; }
    void setTamanho(const QString &tamanho) { this->tamanho = tamanho; }

    int getEstoque() const { return this->estoque; }
    void setEstoque(int estoque) { this->estoque = estoque; }

    float getCusto() const { return this->custo; }
    void setCusto(float custo) { this->custo = custo; }

    int getIdTecido() const { return this->idTecido; }
    void setIdTecido(int idTecido) { this->idTecido = idTecido; }

    QString toString();

    virtual void aumentarEstoque(int qtd) = 0;
    virtual void diminuirEstoque(int qtd) = 0;

protected:
    int id;
    QString nome;
    QString tipo;
    QString tamanho;
    int estoque;
    float custo;
    int idTecido;
};

#endif // ROUPAMODEL_H