#include "ConjuntoView.h"

void ConjuntoView::load() {
    while(numInput != 5) {
        out << "~~~~~~~~~~~~~~~~~\n"
            << "PÁGINA DE TECIDOS\n"
            << "~~~~~~~~~~~~~~~~~\n";

        // limpa a listaConjuntos sempre que a pagina for carregada novamente
        qDeleteAll(listaConjuntos);
        listaConjuntos.clear();

        // imprime os conjuntos cadastrados
        this->listaConjuntos = conDao.getAll();
        for (ConjuntoModel* con : std::as_const(listaConjuntos)) {
            out << "_________________\n";
            out << con->toString();
        }

        out << "\nQual operação deseja fazer?\n";
        out << "[1] Novo conjunto\n"
            << "[2] Editar conjunto (pelo ID)\n"
            << "[3] Remover conjunto (pelo ID)\n"
            << "[4] Atualizar estoque (pelo ID)\n"
            << "[5] Voltar\n";
        out.flush();

        QString input = in.readLine();
        numInput = input.toInt();

        out << "\n";

        switch (numInput) {
        case 1:
            form(false);
            break;
        case 2:
            form(true);
            break;
        case 3:
            remover();
            break;
        case 4:
            gerenciarEstoque();
            break;
        case 5:
            out << "\033[H\033[J";
            break;
        default:
            out << "\033[H\033[J";
            out << "[AVISO] Resposta inválida. Tente novamente:\n";
            break;
        }
    }
}
