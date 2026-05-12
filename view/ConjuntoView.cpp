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

ConjuntoModel* ConjuntoView::validarId() {
    out << "ID do conjunto a ser manipulado: ";
    out.flush();

    QString id = in.readLine();
    validarVazio(id);

    while (!id.toInt()) {
        out << "Escreva um número. Tente novamente:";
        out.flush();
        id = in.readLine();
    }

    while (id.toInt() < 0) {
        out << "Escreva um número positivo. Tente novamente:";
        out.flush();
        id = in.readLine();
    }

    ConjuntoModel* c = conDao.getById(id.toInt());
    return c;
}

void ConjuntoView::remover()
{
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~\n"
        << "REMOVER CONJUNTO\n"
        << "~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    // pede e valida o id do conjunto
    ConjuntoModel* conAtual = validarId();

    if (conAtual == nullptr) {
        out << "\n[AVISO] ID inválido. Busque o ID correto.";
        delete conAtual;
        retornar();
        return;
    }

    // mostra o conjunto antes de tentar remover
    out << "\nConjunto encontrado:\n";
    out << conAtual->toString();

    // confirmacao para evitar remocao por engano
    out << "\nTem certeza que deseja remover este conjunto?"
           "\nAs roupas vinculadas a ele ainda estarão registradas no sistema [s/n]: ";
    out.flush();

    QString confirmacao = in.readLine().toLower();

    if (confirmacao == "s") {
        if (conDao.remove(conAtual->getId())) {
            out << "\n[SUCESSO] Conjunto removido!";
        } else {
            out << "\n[ERRO] Não foi possível remover o conjunto.";
        }
    } else {
        out << "\n[AVISO] Remoção cancelada.";
    }

    delete conAtual;
    retornar();
}