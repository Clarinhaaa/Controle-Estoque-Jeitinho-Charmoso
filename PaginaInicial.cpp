#include "PaginaInicial.h"
#include "TecidoView.h"
#include "ConjuntoView.h"  // adicionado para RF009

void PaginaInicial::load() {
    QTextStream in(stdin);
    QTextStream out(stdout);

    TecidoView teciView;
    ConjuntoView conjView;  // adicionado para RF009

    while(numInput != 4) {
        out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            << "‧₊˚❀༉‧₊˚. CONTROLE DE ESTOQUE: JEITINHO CHARMOSO ‧₊˚❀༉‧₊˚.\n"
            << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        out << "Qual estoque deseja ver?\n";
        out << "[1] Tecidos\n" << "[2] Roupas\n" << "[3] Conjuntos\n" << "[4] Sair\n";
        out.flush();

        QString input = in.readLine();
        numInput = input.toInt();

        out << "\n\n";

        switch (numInput) {
        case 1:
            teciView.load();
            break;
        case 2:
            // RF de roupas ainda não implementado
            break;
        case 3:
            // chama a página de conjuntos - RF009
            conjView.load();
            break;
        case 4:
            out << "Encerrando...\n";
            break;
        default:
            out << "\033[H\033[J";
            out << "[AVISO] Resposta invalida. Tente novamente:\n";
            break;
        }
    }
}