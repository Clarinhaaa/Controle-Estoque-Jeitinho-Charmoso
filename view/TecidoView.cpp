#include "TecidoView.h"

void TecidoView::load() {
    while(numInput != 5) {
        out << "~~~~~~~~~~~~~~~~~\n"
            << "PÁGINA DE TECIDOS\n"
            << "~~~~~~~~~~~~~~~~~\n";

        // limpa a listaTecidos sempre que a página for carregada novamente
        qDeleteAll(listaTecidos);
        listaTecidos.clear();

        // imprime os tecidos cadastrados
        this->listaTecidos = teciDao.getAll();
        for (TecidoModel* teci : std::as_const(listaTecidos)) {
            out << "_________________\n";
            out << teci->toString();
        }

        out << "\nQual operação deseja fazer?\n";
        out << "[1] Novo tecido\n"
            << "[2] Editar tecido (pelo ID)\n"
            << "[3] Remover tecido (pelo ID)\n"
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
            // chama a função criada para remover tecido pelo id
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
            out << "[AVISO] Resposta invalida. Tente novamente:\n";
            break;
        }
    }
}

TecidoModel* TecidoView::validarId() {
    out << "ID do tecido a ser manipulado: ";
    out.flush();

    QString id = in.readLine();
    validarVazio(id);

    while (!id.toInt() || id.toInt() < 0) {
        out << "Escreva um número positivo. Tente novamente:";
        out.flush();
        id = in.readLine();
    }

    // verifica se o ID corresponde a um tecido no banco
    TecidoModel* t = teciDao.getById(id.toInt());
    return t;
}

void TecidoView::form(bool isEdicao) {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~\n"
        << ((!isEdicao) ? "NOVO TECIDO\n" : "EDITAR TECIDO\n")
        << "~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    TecidoModel* novoTecido;

    // caso seja para edição, pede o ID do tecido a ser atualizado
    if (isEdicao) {
        novoTecido = validarId();

        if (novoTecido == nullptr) {
            out << "\nID inválido. Busque o ID correto.";
            delete novoTecido;
            retornar();
            return;
        }
    } else {
        novoTecido = new TecidoModel();
    }

    // preenchendo os campos e validando
    out << "Estampa" << ((isEdicao) ? " (valor atual: " + novoTecido->getEstampa() + ")" : "") << ": ";
    out.flush();

    QString estampa = in.readLine();
    validarVazio(estampa);
    novoTecido->setEstampa(estampa);

    out << "\nMaterial" << ((isEdicao) ? " (valor atual: " + novoTecido->getMaterial() + ")" : "") << ": ";
    out.flush();

    QString material = in.readLine();
    validarVazio(material);
    novoTecido->setMaterial(material);

    if (!isEdicao) {
        out << "\nMetros: ";
        out.flush();

        QString metros = in.readLine();
        validarVazio(metros);

        while (!metros.toFloat() || metros.toFloat() < 0) {
            out << "Escreva um número positivo. Tente novamente:";
            out.flush();
            metros = in.readLine();
        }

        novoTecido->setMetros(metros.toFloat());
    }

    out << "\nCusto" << ((isEdicao) ? " (valor atual: " + QString::number(novoTecido->getCusto()) + ")" : "") << ": ";
    out.flush();

    QString custo = in.readLine();
    validarVazio(custo);

    while (!custo.toFloat() || custo.toFloat() < 0) {
        out << "Escreva um número positivo. Tente novamente:";
        out.flush();
        custo = in.readLine();
    }

    novoTecido->setCusto(custo.toFloat());

    // salvando no banco
    if (!isEdicao) {
        if (teciDao.insert(novoTecido)) {
            out << "[SUCESSO] Tecido cadastrado!";
        } else {
            out << "[ERRO] Não foi possível realizar o cadastro.";
        }
    } else {
        if (teciDao.update(novoTecido)) {
            out << "[SUCESSO] Tecido atualizado!";
        } else {
            out << "[ERRO] Não foi possível atualizar o tecido.";
        }
    }

    delete novoTecido;

    retornar();
}

void TecidoView::validarVazio(QString campo) {
    while (campo.isEmpty()) {
        out << "Não deixe o campo vazio. Tente novamente:";
        out.flush();
        campo = in.readLine();
    }
}

void TecidoView::retornar() {
    out << "\nPressione Enter para voltar...";
    out.flush();
    in.readLine();
}

void TecidoView::gerenciarEstoque() {
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "GERENCIAR ESTOQUE DE TECIDOS\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    // pedindo o ID
    TecidoModel* tecidoAtual = validarId();

    if (tecidoAtual == nullptr) {
        out << "\nID inválido. Busque o ID correto.";
        delete tecidoAtual;
        retornar();
        return;
    }

    out << "\n[1] Aumentar estoque" << "\n[2] Diminuir estoque\n";
    out.flush();

    int input = in.readLine().toInt();

    while (input < 1 || input > 2) {
        out << "\nResposta inválida. Tente novamente: ";
        out.flush();
        input = in.readLine().toInt();
    }

    out << "\nQuantidade (em metros): ";
    out.flush();

    float qtd = in.readLine().toFloat();

    while (qtd <= 0) {
        out << "\nInsira um número positivo: ";
        out.flush();
        qtd = in.readLine().toFloat();
    }

    if (input == 1) {
        tecidoAtual->aumentarEstoque(qtd);
    } else {
        tecidoAtual->diminuirEstoque(qtd);
    }

    // salvando alterações no banco
    if (teciDao.update(tecidoAtual)) {
        out << "[SUCESSO] Estoque atualizado!";
    } else {
        out << "[ERRO] Não foi possível atualizar o estoque.";
    }

    delete tecidoAtual;
    retornar();
}

// remove um tecido do banco pelo id
// metodo adicionado para implementar o RF018 - remocao de tecidos
void TecidoView::remover()
{
    out << "\033[H\033[J";
    out << "~~~~~~~~~~~~~~~~\n"
        << "REMOVER TECIDO\n"
        << "~~~~~~~~~~~~~~~~\n\n";
    out.flush();

    // pede e valida o id do tecido
    TecidoModel* tecidoAtual = validarId();

    if (tecidoAtual == nullptr) {
        out << "\nID inválido. Busque o ID correto.";
        delete tecidoAtual;
        retornar();
        return;
    }

    // mostra o tecido antes de remover
    out << "\nTecido encontrado:\n";
    out << tecidoAtual->toString();

    // confirmação para evitar remoção por engano
    out << "\nTem certeza que deseja remover este tecido? [s/n]: ";
    out.flush();

    QString confirmacao = in.readLine().toLower();

    if (confirmacao == "s") {
        if (teciDao.remove(tecidoAtual->getId())) {
            out << "\n[SUCESSO] Tecido removido!";
        } else {
            out << "\n[ERRO] Não foi possível remover o tecido.";
        }
    } else {
        out << "\n[AVISO] Remoção cancelada.";
    }

    delete tecidoAtual;
    retornar();
}