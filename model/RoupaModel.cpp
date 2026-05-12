#include "RoupaModel.h"

RoupaModel::RoupaModel() : id(0), estoque(0), custo(0.0f) {}

int RoupaModel::getId() const { return id; }
void RoupaModel::setId(int newId) { id = newId; }

QString RoupaModel::getNome() const { return nome; }
void RoupaModel::setNome(const QString &newNome) { nome = newNome; }

QString RoupaModel::getTipo() const { return tipo; }
void RoupaModel::setTipo(const QString &newTipo) { tipo = newTipo; }

QString RoupaModel::getTamanho() const { return tamanho; }
void RoupaModel::setTamanho(const QString &newTamanho) { tamanho = newTamanho; }

int RoupaModel::getEstoque() const { return estoque; }
void RoupaModel::setEstoque(int newEstoque) { estoque = newEstoque; }

float RoupaModel::getCusto() const { return custo; }
void RoupaModel::setCusto(float newCusto) { custo = newCusto; }
