#include "ConjuntoView.h"

void ConjuntoView::load() {
    while(numInput != 5) {
<<<<<<< HEAD
        out << "~~~~~~~~~~~~~~~~~~~\n"
            << "PÁGINA DE CONJUNTOS\n"
            << "~~~~~~~~~~~~~~~~~~~\n";

        // limpa a listaConjuntos sempre que a página for carregada novamente
        qDeleteAll(listaConjuntos);
        listaConjuntos.clear();

        // busca e imprime todos os conjuntos cadastrados no banco
        this->listaConjuntos = conjDao.getAll();
        for (RoupaConjuntoModel* conj : std::as_const(listaConjuntos)) {
            out << "___________________\n";
            out << conj->toString();
        }

        // exibe o menu de ações disponíveis
=======
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

>>>>>>> b4d350c06109df522c7ee42226ee271c0e67b4a3
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
<<<<<<< HEAD
            // chama o form em modo edição
            form(true);
            break;
        case 3:
            // chama a função criada para remover conjunto pelo id
=======
            form(true);
            break;
        case 3:
>>>>>>> b4d350c06109df522c7ee42226ee271c0e67b4a3
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
<<<<<<< HEAD

// pede e valida o ID do conjunto, retornando o objeto do banco
RoupaConjuntoModel* ConjuntoView::validarId() {
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

    // verifica se o ID corresponde a um conjunto no banco
    RoupaConjuntoModel* c = conjDao.getById(id.toInt());
    return c;
}

// formulário de cadastro (isEdicao=false) e edição (isEdicao=true)
void ConjuntoView::form(bool isEdicao) {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~~~\n"
        << ((!isEdicao) ? "NOVO CONJUNTO\n" : "EDITAR CONJUNTO\n")
        << "~~~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    RoupaConjuntoModel* novoConj;

    // caso seja edição, pede o ID do conjunto a ser atualizado
    if (isEdicao) {
        novoConj = validarId();

        if (novoConj == nullptr) {
            out << "\nID inválido. Busque o ID correto.";
            delete novoConj;
            retornar();
            return;
        }
    } else {
        novoConj = new RoupaConjuntoModel();
    }

    // --- preenchendo e validando cada campo ---

    out << "Nome" << ((isEdicao) ? " (valor atual: " + novoConj->getNome() + ")" : "") << ": ";
    out.flush();
    QString nome = in.readLine();
    validarVazio(nome);
    novoConj->setNome(nome);

    // exibe as opções de tipo predefinidas no model
    out << "\nTipo" << ((isEdicao) ? " (valor atual: " + novoConj->getTipo() + ")" : "") << ":\n";
    for (int i = 0; i < RoupaModel::OPCOES_TIPO.size(); ++i) {
        out << "[" << (i + 1) << "] " << RoupaModel::OPCOES_TIPO[i] << "\n";
    }
    out.flush();
    int tipoIdx = in.readLine().toInt();
    while (tipoIdx < 1 || tipoIdx > RoupaModel::OPCOES_TIPO.size()) {
        out << "Opção inválida. Tente novamente: ";
        out.flush();
        tipoIdx = in.readLine().toInt();
    }
    novoConj->setTipo(RoupaModel::OPCOES_TIPO[tipoIdx - 1]);

    // exibe as opções de tamanho predefinidas no model
    out << "\nTamanho" << ((isEdicao) ? " (valor atual: " + novoConj->getTamanho() + ")" : "") << ":\n";
    for (int i = 0; i < RoupaModel::OPCOES_TAMANHO.size(); ++i) {
        out << "[" << (i + 1) << "] " << RoupaModel::OPCOES_TAMANHO[i] << "\n";
    }
    out.flush();
    int tamIdx = in.readLine().toInt();
    while (tamIdx < 1 || tamIdx > RoupaModel::OPCOES_TAMANHO.size()) {
        out << "Opção inválida. Tente novamente: ";
        out.flush();
        tamIdx = in.readLine().toInt();
    }
    novoConj->setTamanho(RoupaModel::OPCOES_TAMANHO[tamIdx - 1]);

    out << "\nFornecedor" << ((isEdicao) ? " (valor atual: " + novoConj->getFornecedor() + ")" : "") << ": ";
    out.flush();
    QString fornecedor = in.readLine();
    validarVazio(fornecedor);
    novoConj->setFornecedor(fornecedor);

    out << "\nCusto" << ((isEdicao) ? " (valor atual: " + QString::number(novoConj->getCusto()) + ")" : "") << ": ";
    out.flush();
    QString custo = in.readLine();
    validarVazio(custo);
    while (!custo.toFloat() || custo.toFloat() < 0) {
        out << "Escreva um número positivo. Tente novamente: ";
        out.flush();
        custo = in.readLine();
    }
    novoConj->setCusto(custo.toFloat());

    out << "\nID do Tecido" << ((isEdicao) ? " (valor atual: " + QString::number(novoConj->getIdTecido()) + ")" : "") << ": ";
    out.flush();
    QString idTecido = in.readLine();
    validarVazio(idTecido);
    while (!idTecido.toInt() || idTecido.toInt() < 0) {
        out << "Escreva um número positivo. Tente novamente: ";
        out.flush();
        idTecido = in.readLine();
    }
    novoConj->setIdTecido(idTecido.toInt());

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

    // salvando no banco
    if (!isEdicao) {
        if (conjDao.insert(novoConj)) {
            out << "\n[SUCESSO] Conjunto cadastrado!";
        } else {
            out << "\n[ERRO] Não foi possível realizar o cadastro.";
        }
    } else {
        if (conjDao.update(novoConj)) {
            out << "\n[SUCESSO] Conjunto atualizado!";
        } else {
            out << "\n[ERRO] Não foi possível atualizar o conjunto.";
        }
    }

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

    // pede e valida o ID do conjunto
    RoupaConjuntoModel* conjAtual = validarId();

    if (conjAtual == nullptr) {
        out << "\nID inválido. Busque o ID correto.";
        delete conjAtual;
        retornar();
        return;
    }

    out << "\n[1] Aumentar estoque\n[2] Diminuir estoque\n";
    out.flush();

    int input = in.readLine().toInt();
    while (input < 1 || input > 2) {
        out << "\nResposta inválida. Tente novamente: ";
        out.flush();
        input = in.readLine().toInt();
    }

    out << "\nQuantidade (em unidades): ";
    out.flush();
    int qtd = in.readLine().toInt();
    while (qtd <= 0) {
        out << "\nInsira um número positivo: ";
        out.flush();
        qtd = in.readLine().toInt();
    }

    if (input == 1) {
        conjAtual->aumentarEstoque(qtd);
    } else {
        conjAtual->diminuirEstoque(qtd);
    }

    // salva as alterações de estoque no banco
    if (conjDao.update(conjAtual)) {
        out << "[SUCESSO] Estoque atualizado!";
    } else {
        out << "[ERRO] Não foi possível atualizar o estoque.";
    }

    delete conjAtual;
    retornar();
}

// remove um conjunto do banco pelo ID com confirmação do usuário
void ConjuntoView::remover() {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~~\n"
        << "REMOVER CONJUNTO\n"
        << "~~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    // pede e valida o ID do conjunto
    RoupaConjuntoModel* conjAtual = validarId();

    if (conjAtual == nullptr) {
        out << "\n[AVISO] ID inválido. Busque o ID correto.";
        delete conjAtual;
        retornar();
        return;
    }

    // mostra o conjunto antes de confirmar a remoção
    out << "\nConjunto encontrado:\n";
    out << conjAtual->toString();

    // confirmação para evitar remoção por engano
    out << "\nTem certeza que deseja remover este conjunto? [s/n]: ";
    out.flush();
    QString confirmacao = in.readLine().toLower();

    if (confirmacao == "s") {
        if (conjDao.remove(conjAtual->getId())) {
            out << "\n[SUCESSO] Conjunto removido!";
        } else {
            out << "\n[ERRO] Não foi possível remover o conjunto.";
        }
    } else {
        out << "\n[AVISO] Remoção cancelada.";
    }

    delete conjAtual;
    retornar();
}
=======
>>>>>>> b4d350c06109df522c7ee42226ee271c0e67b4a3
