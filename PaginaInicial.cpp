#include "PaginaInicial.h"
#include "dao/RoupaConjuntoDao.h"
#include "view/TecidoView.h"
#include <iostream>
#include <QTextStream>

using namespace std;

PaginaInicial::PaginaInicial() {}

void PaginaInicial::load() {
    QTextStream in(stdin);
    int numInput = -1;

    while (numInput != 4) {
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "  * .  CONTROLE DE ESTOQUE: JEITINHO CHARMOSO  .  * \n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Qual estoque deseja ver?\n";
        cout << "[1] Tecidos\n";
        cout << "[2] Roupas\n";
        cout << "[3] Conjuntos (Excluir RF012)\n";
        cout << "[4] Sair\n";
        cout << "Opcao: ";
        
        QString input = in.readLine();
        numInput = input.toInt();

        switch (numInput) {
            case 1:
                {
                    TecidoView teciView;
                    teciView.load();
                }
                break;
            case 2:
             
                break;
            case 3:
                menuExcluirConjunto();
                break;
            case 4:
                cout << "Encerrando...\n";
                break;
            default:
                cout << "[AVISO] Resposta invalida. Tente novamente:\n";
                break;
        }
    }
}

void PaginaInicial::menuExcluirConjunto() {
    int idParaExcluir;
    char confirmacao;

    cout << "\n---- EXCLUSAO DE CONJUNTO ----" << endl;
    cout << "Digite o ID do conjunto que deseja remover: ";
    cin >> idParaExcluir;

    cout << "AVISO: Tem certeza que deseja excluir o conjunto " << idParaExcluir << "? (s/n): ";
    cin >> confirmacao;

    if (confirmacao == 's' || confirmacao == 'S') {
        RoupaConjuntoDao dao;
        if (dao.removerConjunto(idParaExcluir)) {
            cout << ">>> SUCESSO: O conjunto foi removido do sistema." << endl;
        } else {
            cout << ">>> ERRO: Nao foi possivel remover. Verifique se o ID existe." << endl;
        }
    } else {
        cout << ">>> Operacao cancelada." << endl;
    }
}