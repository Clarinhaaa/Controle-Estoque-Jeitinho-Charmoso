#ifndef PAGINA_H
#define PAGINA_H

#include <QTextStream>
#include <QIODevice>

class Pagina // classe abstrata de onde todas as views herdam
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

    void validarNumPositivo(QString num) {
        while (!num.toInt() && !num.toFloat()) {
            out << "Escreva um número. Tente novamente:";
            out.flush();
            num = in.readLine();
        }

        while (num.toFloat() < 0 || num.toInt() < 0) {
            out << "Escreva um número positivo. Tente novamente:";
            out.flush();
            num = in.readLine();
        }
    }

    virtual void load() = 0;
    void form(bool isEdicao);
    void gerenciarEstoque();
    void remover();
};

#endif // PAGINA_H
