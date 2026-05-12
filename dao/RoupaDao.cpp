#include "dao/RoupaDao.h"
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>

using namespace std;

RoupaDao::RoupaDao() {}

void RoupaDao::verificarEstoqueBaixo() {
    QSqlQuery query;
    query.prepare("SELECT nome_roupa, estoque_roupa FROM Roupa WHERE estoque_roupa <= 5");

    cout << "\n========== ALERTA DE ESTOQUE BAIXO ==========" << endl;
    if (query.exec()) {
        bool encontrou = false;
        while (query.next()) {
            encontrou = true;
            string nome = query.value("nome_roupa").toString().toStdString();
            int qtd = query.value("estoque_roupa").toInt();
            cout << "[!] ITEM: " << nome << " | QTD: " << qtd << endl;
        }
        if (!encontrou) cout << "Estoque em niveis seguros." << endl;
    }
    cout << "=============================================" << endl;
}

// RF005 - Remoção de Roupa
bool RoupaDao::removerRoupa(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Roupa WHERE id_roupa = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        cout << "\n[INFO] Tentativa de remocao do ID " << id << " concluida." << endl;
        return true;
    }
    return false;
}