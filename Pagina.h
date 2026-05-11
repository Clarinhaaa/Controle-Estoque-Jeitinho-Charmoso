#ifndef PAGINA_H
#define PAGINA_H

#include <QTextStream>
#include <QIODevice>

class Pagina
{
public:
    Pagina() : in(stdin, QIODevice::ReadOnly), out(stdout, QIODevice::WriteOnly) {
        this->numInput = 0;
        out.setEncoding(QStringConverter::Utf8);
    }
    virtual ~Pagina() {}

    virtual void load() = 0;
protected:
    int numInput;
    QTextStream in;
    QTextStream out;
};

#endif // PAGINA_H
