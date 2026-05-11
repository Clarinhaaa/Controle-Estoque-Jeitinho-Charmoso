#ifndef TECIDOMODEL_H
#define TECIDOMODEL_H

#include <QString>

class TecidoModel
{
private:
    int id;
    QString estampa;
    QString material;
    float metros;
    float custo;
public:
    TecidoModel() {};
    TecidoModel(int id, const QString& estampa, const QString& material, float metros, float custo);
    ~TecidoModel() {};

    int getId() const { return this->id; }
    void setId(int id) { this->id = id; }

    const QString& getEstampa() const { return this->estampa; }
    void setEstampa(const QString& estampa) {this->estampa = estampa; }

    const QString& getMaterial() const { return this->material; }
    void setMaterial(const QString& material) {this->material = material; }

    float getMetros() const { return this->metros; }
    void setMetros(float metros) { this->metros = metros; }

    float getCusto() const { return this->custo; }
    void setCusto(float custo) { this->custo = custo; }

    QString toString();

    void aumentarEstoque(float qtd);
    void diminuirEstoque(float qtd);
};

#endif // TECIDOMODEL_H
