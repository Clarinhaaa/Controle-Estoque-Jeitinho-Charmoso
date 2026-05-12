#include "RoupaView.h"

void RoupaView::load() {
    while(numInput != 5) {
        out << "~~~~~~~~~~~~~~~~~\n"
            << "PÁGINA DE ROUPAS\n"
            << "~~~~~~~~~~~~~~~~~\n";

        // limpa a listaRoupas sempre que a pagina for carregada novamente
        qDeleteAll(listaRoupas);
        listaRoupas.clear();

        // imprime as roupas cadastradas
        this->listaRoupas = rDao.getAll();
        for (RoupaModel* r : std::as_const(listaRoupas)) {
            out << "_________________\n";
            out << r->toString();
        }

        // mostra roupas com estoque baixo
        const QList<QString> listaEstoqueBaixo = rDao.verificarEstoqueBaixo();
        if (!listaEstoqueBaixo.empty()) {
            out << "\n[AVISO] Roupas com estoque baixo:\n";
            for (const QString& str : listaEstoqueBaixo) {
                out << str << "\n";
            }
        }

        out << "\nQual operação deseja fazer?\n";
        out << "[1] Nova roupa\n"
            << "[2] Editar roupa (pelo ID)\n"
            << "[3] Remover roupa (pelo ID)\n"
            << "[4] Atualizar estoque (pelo ID)\n"
            << "[5] Voltar\n";
        out.flush();

        QString input = in.readLine();
        numInput = input.toInt();

        out << "\n";

        switch (numInput) {
        case 1:
            // perguntar qual tipo de roupa
            break;
        case 2:
            // identificar tipo da roupa
            break;
        case 3:
            // chama a função criada para remover roupa pelo id
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

void RoupaView::remover() {}

void RoupaView::gerenciarEstoque() {}