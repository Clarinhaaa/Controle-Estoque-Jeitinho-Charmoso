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
protected:
    int numInput;
    QTextStream in;
    QTextStream out;

    void retornar() {
        out << "\nPressione Enter para voltar...";
        out.flush();
        in.readLine();
    }

    void validarVazio(QString campo) {
        while (campo.isEmpty()) {
            out << "Não deixe o campo vazio. Tente novamente:";
            out.flush();
            campo = in.readLine();
        }
    }

    virtual void load() = 0;
};

#endif // PAGINA_H
