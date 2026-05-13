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

void RoupaView::form(bool isEdicao) {}

RoupaModel* RoupaView::validarId() {
    out << "ID da roupa a ser manipulada: ";
    out.flush();

    QString id = in.readLine();
    validarVazio(id);
    validarNumPositivo(id);

    RoupaModel* r = rDao.getById(id.toInt());
    return r;
}

void RoupaView::remover() {}

void RoupaView::gerenciarEstoque() {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "GERENCIAR ESTOQUE DE ROUPAS\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    // pedindo o ID
    RoupaModel* roupaAtual = validarId();

    if (roupaAtual == nullptr) {
        out << "\nID inválido. Busque o ID correto.";
        delete roupaAtual;
        retornar();
        return;
    }

    out << "\n[1] Aumentar estoque" << "\n[2] Diminuir estoque\n";
    out.flush();

    QString input = in.readLine();
    validarVazio(input);
    validarNumPositivo(input);

    while (input.toInt() < 1 || input.toInt() > 2) {
        out << "\nResposta inválida. Tente novamente: ";
        out.flush();
        input = in.readLine();
        validarVazio(input);
        validarNumPositivo(input);
    }

    out << "\nQuantidade: ";
    out.flush();

    QString qtd = in.readLine();
    validarVazio(qtd);
    validarNumPositivo(qtd);

    if (input.toInt() == 1) {
        roupaAtual->aumentarEstoque(qtd.toInt());
    } else {
        roupaAtual->diminuirEstoque(qtd.toInt());
    }

    // salvando alteracoes no banco - FALTA UPDATE NO DAO
    /*if (rDao.update(roupaAtual)) {
        out << "[SUCESSO] Estoque atualizado!";
    } else {
        out << "[ERRO] Não foi possível atualizar o estoque.";
    }*/

    delete roupaAtual;
    retornar();
}