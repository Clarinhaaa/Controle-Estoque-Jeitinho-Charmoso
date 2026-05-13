#include "ConjuntoView.h"

void ConjuntoView::load() {
    while(numInput != 5) {
        out << "~~~~~~~~~~~~~~~~~~~\n"
            << "PÁGINA DE CONJUNTOS\n"
            << "~~~~~~~~~~~~~~~~~~~\n";

        // limpa a listaConjuntos sempre que a página for carregada novamente
        qDeleteAll(listaConjuntos);
        listaConjuntos.clear();

        // busca e imprime todos os conjuntos cadastrados no banco
        this->listaConjuntos = conjDao.getAll();
        for (ConjuntoModel* conj : std::as_const(listaConjuntos)) {
            out << "___________________\n";
            out << conj->toString();
        }

        // mostra conjuntos com estoque baixo
        const QList<QString> listaEstoqueBaixo = conDao.verificarEstoqueBaixo();
        if (!listaEstoqueBaixo.empty()) {
            out << "\n[AVISO] Conjuntos com estoque baixo:\n";
            for (const QString& str : listaEstoqueBaixo) {
                out << str << "\n";
            }
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
            // chama o form em modo edição
            form(true);
            break;
        case 3:
            // chama a função criada para remover conjunto pelo id
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
    validarNumPositivo(id);

    ConjuntoModel* c = conDao.getById(id.toInt());
    return c;
}

// formulário de cadastro (isEdicao=false) e edição (isEdicao=true)
void ConjuntoView::form(bool isEdicao) {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~~~\n"
        << ((!isEdicao) ? "NOVO CONJUNTO\n" : "EDITAR CONJUNTO\n")
        << "~~~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    ConjuntoModel* novoConj;

    // caso seja edição, pede o ID do conjunto a ser atualizado
    if (isEdicao) {
        novoConj = validarId();

        if (novoConj == nullptr) {
            out << "\nID inválido. Busque o ID correto.";
            retornar();
            return;
        }
    } else {
        novoConj = new ConjuntoModel();
    }

    out << "Nome" << ((isEdicao) ? " (valor atual: " + novoConj->getNome() + ")" : "") << ": ";
    out.flush();
    QString nome = in.readLine();
    validarVazio(nome);
    novoConj->setNome(nome);

    out << "\nPreço: ";
    out.flush();
    QString preco = in.readLine();
    validarVazio(preco);
    validarNumPositivo(preco);
    novoConj->setPreco(preco.toFloat());

    // estoque só é definido no cadastro; na edição usa gerenciarEstoque()
    if (!isEdicao) {
        out << "\nEstoque inicial (unidades): ";
        out.flush();
        QString estoque = in.readLine();
        validarVazio(estoque);
        validarNumPositivo(preco);
        novoConj->setEstoque(estoque.toInt());
    }

    out << "\n[AVISO] Cadastro/edição ainda não disponível — DAO incompleto.\n";

    delete novoConj;
    retornar();
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

void ConjuntoView::gerenciarEstoque() {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "GERENCIAR ESTOQUE DE CONJUNTOS\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    // pedindo o ID
    ConjuntoModel* conAtual = validarId();

    if (conAtual == nullptr) {
        out << "\nID inválido. Busque o ID correto.";
        delete conAtual;
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
        conAtual->aumentarEstoque(qtd.toInt());
    } else {
        conAtual->diminuirEstoque(qtd.toInt());
    }

    // salvando alteracoes no banco - FALTA UPDATE NO DAO
    /*if (conDao.update(conAtual)) {
        out << "[SUCESSO] Estoque atualizado!";
    } else {
        out << "[ERRO] Não foi possível atualizar o estoque.";
    }*/

    delete conAtual;
    retornar();
}