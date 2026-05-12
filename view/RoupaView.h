#ifndef ROUPAVIEW_H
#define ROUPAVIEW_H

#include "Pagina.h"

class RoupaView : public Pagina
{
public:
    RoupaView() : Pagina() {}
    ~RoupaView() {}

    void load() override;

private:
    void cadastrarRoupa();
    void listarRoupas();
};

#endif // ROUPAVIEW_H
