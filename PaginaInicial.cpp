#include "PaginaInicial.h"
#include "model/RoupaModel.h"
#include <iostream>

using namespace std;

// Implementação do construtor
PaginaInicial::PaginaInicial() {
    // Pode deixar vazio ou inicializar algo
}


void PaginaInicial::load() {
    cout << "--- BEM VINDO AO SISTEMA ---" << endl;
    cadastrarNovaRoupa(); // Chama a função de teste
}

// Implementação do Cadastro (RF013)
void PaginaInicial::cadastrarNovaRoupa() {
    int escTipo, escTam;

    cout << "\nSelecione o TIPO (RF013):" << endl;
    for (int i = 0; i < RoupaModel::OPCOES_TIPO.size(); ++i) {
        cout << i + 1 << " - " << RoupaModel::OPCOES_TIPO[i].toStdString() << endl;
    }
    cin >> escTipo;

    cout << "\nSelecione o TAMANHO (RF013):" << endl;
    for (int i = 0; i < RoupaModel::OPCOES_TAMANHO.size(); ++i) {
        cout << i + 1 << " - " << RoupaModel::OPCOES_TAMANHO[i].toStdString() << endl;
    }
    cin >> escTam;

    QString tipoFinal = RoupaModel::OPCOES_TIPO.value(escTipo - 1, "Outro");
    QString tamFinal = RoupaModel::OPCOES_TAMANHO.value(escTam - 1, "Unico");

    cout << "\n[OK] Selecionado: " << tipoFinal.toStdString() << " " << tamFinal.toStdString() << endl;
}