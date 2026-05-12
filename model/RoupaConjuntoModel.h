#ifndef ROUPACONJUNTOMODEL_H
#define ROUPACONJUNTOMODEL_H

#include "RoupaModel.h"

class RoupaConjuntoModel : public RoupaModel
{
private:
    int idConjunto;

public:
    RoupaConjuntoModel();

    int getIdConjunto() const;
    void setIdConjunto(int newIdConjunto);

};

#endif // ROUPACONJUNTOMODEL_H
