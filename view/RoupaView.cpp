#include "RoupaView.h"
#include "RoupaUnicaModel.h"
#include "RoupaConjuntoModel.h"
#include "RoupaUnicaDao.h"
#include "RoupaConjuntoDao.h"
#include <QStringList>
#include "RoupaDao.h"
#include <utility>

void RoupaView::load() {
    numInput = 0;
    while(numInput != 3) {
        out << "\033[H\033[J"; // Limpa a tela
        out << "~~~~~~~~~~~~~~~~~\n"
            << "PÁGINA DE ROUPAS\n"
            << "~~~~~~~~~~~~~~~~~\n\n";

        out << "[1] Nova Roupa\n"
            << "[2] Listar Roupas\n"
            << "[3] Voltar\n";
        out.flush();

        QString input = in.readLine();
        numInput = input.toInt();
        out << "\n";

        switch (numInput) {
        case 1:
            cadastrarRoupa();
            break;
        case 2:
            listarRoupas();
            break; // Sai do loop e volta ao menu principal
        case 3:
            break;
        default:
            out << "[AVISO] Resposta invalida. Pressione Enter para tentar novamente.\n";
            out.flush();
            in.readLine();
            break;
        }
    }
    numInput = 0; // Reseta para a próxima vez que a tela for aberta
}

void RoupaView::cadastrarRoupa() {
    out << "\033[H\033[J";
    out << "=== CADASTRO DE ROUPA ===\n\n";

    out << "Nome da Roupa: "; out.flush();
    QString nome = in.readLine();

    while(nome.isEmpty()) {
        out << "O nome não pode ser vazio! Nome da Roupa: "; out.flush();
        nome = in.readLine();
    }

    out << "Tipo (Digite 1 para Peça Única ou 2 para Peça de Conjunto): "; out.flush();
    int tipoInt = in.readLine().toInt();
    QString tipo = (tipoInt == 2) ? "Conjunto" : "Peça Única";

    QStringList gradeValida = {"2", "4", "6", "8", "10", "12", "14", "16"};
    QString tamanho;

    do {
        out << "Tamanho (2, 4, 6, 8, 10, 12, 14, 16): "; out.flush();
        tamanho = in.readLine().trimmed();

        if (!gradeValida.contains(tamanho)) {
            out << "[ERRO] Tamanho invalido! Por favor, use apenas a grade da loja.\n";
            out.flush();
        }
    } while (!gradeValida.contains(tamanho));


    out << "Custo (R$): "; out.flush();
    float custo = in.readLine().toFloat();

    out << "Estoque Inicial: "; out.flush();
    int estoque = in.readLine().toInt();

    if (tipoInt == 2) {
        out << "ID do Conjunto ao qual esta peça pertence: "; out.flush();
        int idConj = in.readLine().toInt();

        RoupaConjuntoModel novaRoupa;
        novaRoupa.setNome(nome);
        novaRoupa.setTipo(tipo);
        novaRoupa.setTamanho(tamanho);
        novaRoupa.setCusto(custo);
        novaRoupa.setEstoque(estoque);
        novaRoupa.setIdConjunto(idConj);

        RoupaConjuntoDao dao;
        if (dao.insert(novaRoupa)) {
            out << "\n[SUCESSO] Peça de CONJUNTO '" << novaRoupa.getNome() << "' salva no banco de dados!\n";
        } else {
            out << "\n[ERRO] Ocorreu um erro ao salvar no banco de dados.\n";
        }
    } else {
        RoupaUnicaModel novaRoupa;
        novaRoupa.setNome(nome);
        novaRoupa.setTipo(tipo);
        novaRoupa.setTamanho(tamanho);
        novaRoupa.setCusto(custo);
        novaRoupa.setEstoque(estoque);

        RoupaUnicaDao dao;
        if (dao.insert(novaRoupa)) {
            out << "\n[SUCESSO] PEÇA ÚNICA '" << novaRoupa.getNome() << "' salva no banco de dados!\n";
        } else {
            out << "\n[ERRO] Ocorreu um erro ao salvar no banco de dados.\n";
        }
    }

    out << "\nPressione Enter para continuar..."; out.flush();
    in.readLine();
}

void RoupaView::listarRoupas() {
    out << "\033[H\033[J";
    out << "=== LISTA DE ROUPAS CADASTRADAS ===\n\n";

    RoupaDao dao;
    QList<RoupaModel*> lista = dao.getAll();

    if (lista.isEmpty()) {
        out << "Nenhuma roupa cadastrada no momento.\n";
    } else {
        for (RoupaModel* r : std::as_const(lista)) {
            // Imprime os dados gerais
            out << "ID: " << r->getId()
                << " | Nome: " << r->getNome()
                << " | Tipo: " << r->getTipo()
                << " | Tam: " << r->getTamanho()
                << " | Estoque: " << r->getEstoque();


            if (r->getTipo() == "Conjunto") {
                RoupaConjuntoModel* conjunto = dynamic_cast<RoupaConjuntoModel*>(r);
                if (conjunto != nullptr) {
                    out << " | Pertence ao Conjunto ID: " << conjunto->getIdConjunto();
                }
            }
            out << "\n";
        }
    }

    qDeleteAll(lista);

    out << "\nPressione Enter para voltar..."; out.flush();
    in.readLine();
}
