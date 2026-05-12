#include "PaginaInicial.h"
#include "dao/RoupaConjuntoDao.h" // Verifique se o nome do arquivo na pasta Headers/dao é este mesmo
#include <iostream>
#include "view/TecidoView.h"

using namespace std;

// Construtor da classe
PaginaInicial::PaginaInicial() {}

// Função que o main.cpp chama para iniciar o sistema
void PaginaInicial::load() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Cadastrar Roupa" << endl;
        cout << "2. Gerenciar Conjuntos" << endl;
        cout << "3. Excluir Conjunto (RF012)" << endl; // Opção do seu requisito
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 3:
            menuExcluirConjunto(); // Chama a função que criamos
            break;
        case 0:
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
        }
    }
}

// Implementação do Requisito RF012 - Remoção de Conjuntos
void PaginaInicial::menuExcluirConjunto() {
    int idParaExcluir;
    char confirmacao;

    cout << "\n---- EXCLUSAO DE CONJUNTO ----" << endl;
    cout << "Digite o ID do conjunto que deseja remover: ";
    cin >> idParaExcluir;

    // REQUISITO RF012: O sistema DEVE pedir confirmação
    cout << "AVISO: Tem certeza que deseja excluir o conjunto " << idParaExcluir << "? (s/n): ";
    cin >> confirmacao;

    if (confirmacao == 's' || confirmacao == 'S') {
        RoupaConjuntoDao dao; // Criamos o objeto do DAO

        if (dao.removerConjunto(idParaExcluir)) {
            cout << ">>> SUCESSO: O conjunto foi removido do sistema." << endl;
        } else {
            cout << ">>> ERRO: Nao foi possivel remover. Verifique se o ID existe." << endl;
=======
    QTextStream in(stdin);
    QTextStream out(stdout);
    TecidoView teciView;

    while(numInput != 4) {
        out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            << "‧₊˚❀༉‧₊˚. CONTROLE DE ESTOQUE: JEITINHO CHARMOSO ‧₊˚❀༉‧₊˚.\n"
            << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        out << "Qual estoque deseja ver?\n";
        out << "[1] Tecidos\n" << "[2] Roupas\n" << "[3] Conjuntos\n" << "[4] Sair\n";
        out.flush();

        QString input = in.readLine();
        numInput = input.toInt();
        out << "\n\n";

        switch (numInput) {
            case 1:
                teciView.load();
                break;
            case 2:
                // roupaView.load();
                break;
            case 3:
                // conjuntoView.load();
                break;
            case 4:
                out << "Encerrando...\n";
                break;
            default:
                out << "\033[H\033[J";
                out << "[AVISO] Resposta inválida. Tente novamente:\n";
                break;
        }
    } else {
        cout << ">>> OPERACAO CANCELADA. O conjunto permanece no banco." << endl;
    }
}