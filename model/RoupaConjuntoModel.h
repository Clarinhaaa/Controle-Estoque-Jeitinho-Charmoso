#ifndef ROUPACONJUNTOMODEL_H
#define ROUPACONJUNTOMODEL_H
#include <QString>
class RoupaConjuntoModel {
=======
#include "model/RoupaModel.h"

class RoupaConjuntoModel : public RoupaModel
{
public:
    RoupaConjuntoModel(); // Construtor
    int id;
    QString nome;
};
#endif