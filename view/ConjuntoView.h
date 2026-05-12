#ifndef CONJUNTOVIEW_H
#define CONJUNTOVIEW_H

#include <QTextStream>

class ConjuntoView
{
public:
    ConjuntoView();
    void cadastrarConjunto();

private:
    QTextStream out{stdout};
    QTextStream in{stdin};
};

#endif // CONJUNTOVIEW_H
