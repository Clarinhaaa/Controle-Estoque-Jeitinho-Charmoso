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

        // exibe o menu de ações disponíveis
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

// pede e valida o ID do conjunto, retornando o objeto do banco
ConjuntoModel* ConjuntoView::validarId() {
    out << "ID do conjunto a ser manipulado: ";
    out.flush();

    QString id = in.readLine();
    validarVazio(id);

    // garante que o valor digitado é um número
    while (!id.toInt()) {
        out << "Escreva um número. Tente novamente: ";
        out.flush();
        id = in.readLine();
    }

    // garante que o número é positivo
    while (id.toInt() < 0) {
        out << "Escreva um número positivo. Tente novamente: ";
        out.flush();
        id = in.readLine();
    }

    // TODO: substituir por conjDao.getById() quando o método for implementado no DAO
    out << "[AVISO] Busca por ID ainda não disponível.\n";
    return nullptr;
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

    // --- preenchendo e validando cada campo ---

    out << "Nome" << ((isEdicao) ? " (valor atual: " + novoConj->getNome() + ")" : "") << ": ";
    out.flush();
    QString nome = in.readLine();
    validarVazio(nome);
    novoConj->setNome(nome);

    out << "\nPreço: ";
    out.flush();
    QString preco = in.readLine();
    validarVazio(preco);
    while (!preco.toFloat() || preco.toFloat() < 0) {
        out << "Escreva um número positivo. Tente novamente: ";
        out.flush();
        preco = in.readLine();
    }
    novoConj->setPreco(preco.toFloat());

    // estoque só é definido no cadastro; na edição usa gerenciarEstoque()
    if (!isEdicao) {
        out << "\nEstoque inicial (unidades): ";
        out.flush();
        QString estoque = in.readLine();
        validarVazio(estoque);
        while (!estoque.toInt() || estoque.toInt() < 0) {
            out << "Escreva um número positivo. Tente novamente: ";
            out.flush();
            estoque = in.readLine();
        }
        novoConj->setEstoque(estoque.toInt());
    }

    // TODO: chamar conjDao.insert() ou conjDao.update() quando implementados no DAO
    out << "\n[AVISO] Cadastro/edição ainda não disponível — DAO incompleto.\n";

    delete novoConj;
    retornar();
}

// verifica se o campo está vazio e repede enquanto estiver
void ConjuntoView::validarVazio(QString campo) {
    while (campo.isEmpty()) {
        out << "Não deixe o campo vazio. Tente novamente: ";
        out.flush();
        campo = in.readLine();
    }
}

// aguarda o usuário pressionar Enter antes de voltar à listagem
void ConjuntoView::retornar() {
    out << "\nPressione Enter para voltar...";
    out.flush();
    in.readLine();
}

// permite aumentar ou diminuir o estoque de um conjunto pelo ID
void ConjuntoView::gerenciarEstoque() {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "GERENCIAR ESTOQUE DE CONJUNTOS\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    // TODO: disponível quando conjDao.getById() e conjDao.update() forem implementados
    out << "[AVISO] Funcionalidade ainda não disponível — DAO incompleto.\n";
    retornar();
}

// remove um conjunto do banco pelo ID com confirmação do usuário
void ConjuntoView::remover() {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~~\n"
        << "REMOVER CONJUNTO\n"
        << "~~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    // TODO: disponível quando conjDao.getById() e conjDao.remove() forem implementados
    out << "[AVISO] Funcionalidade ainda não disponível — DAO incompleto.\n";
    retornar();
}