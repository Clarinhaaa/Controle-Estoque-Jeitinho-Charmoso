#include <QCoreApplication>
#include <QtSql>
#include <iostream>

using namespace std;

// --- FUNÇÃO QUE CRIA O BANCO SE ELE NÃO EXISTIR ---
void implementarBanco() {
    QSqlQuery q;

    // Ativa suporte a chaves estrangeiras
    q.exec("PRAGMA foreign_keys = ON;");

    // Criação das tabelas conforme seu esquema oficial
    q.exec("CREATE TABLE IF NOT EXISTS Tecido ("
           "id_tecido INTEGER PRIMARY KEY AUTOINCREMENT, material_tecido TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS Roupa ("
           "id_roupa INTEGER PRIMARY KEY AUTOINCREMENT, nome_roupa TEXT, "
           "id_tecido_roupa INTEGER, FOREIGN KEY (id_tecido_roupa) REFERENCES Tecido(id_tecido))");

    q.exec("CREATE TABLE IF NOT EXISTS Conjunto ("
           "id_conjunto INTEGER PRIMARY KEY AUTOINCREMENT, nome_conjunto TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS Conjunto_has_Roupa ("
           "id_conjunto_roupa INTEGER, id_roupa_conjunto INTEGER, "
           "PRIMARY KEY (id_conjunto_roupa, id_roupa_conjunto), "
           "FOREIGN KEY (id_conjunto_roupa) REFERENCES Conjunto(id_conjunto) ON DELETE CASCADE, "
           "FOREIGN KEY (id_roupa_conjunto) REFERENCES Roupa(id_roupa) ON DELETE CASCADE)");

    // VAMOS INSERIR UMA ROUPA DE TESTE PARA VOCÊ PODER DELETAR
    q.exec("INSERT INTO Roupa (nome_roupa) VALUES ('Roupa de Teste Vivi')");
    cout << "\n[BANCO] Tabelas conferidas/criadas e dado de teste inserido!" << endl;
}

void removerRoupa() {
    int id;
    cout << "\nDigite o ID da roupa para remover (Tente o ID 1): ";
    cin >> id;

    QSqlQuery query;
    query.prepare("DELETE FROM Roupa WHERE id_roupa = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.numRowsAffected() > 0) {
        cout << ">>> SUCESSO: Roupa " << id << " removida!" << endl;
    } else {
        cout << ">>> ERRO: ID nao encontrado." << endl;
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("loja.sqlite");

    if (!db.open()) {
        cout << "Nao foi possivel criar/abrir o banco!";
        return -1;
    }

    implementarBanco(); // Aqui ele cria as tabelas automaticamente
    removerRoupa();     // Aqui você testa a remoção

    cout << "\nFim do teste. Verifique a pasta build para ver o arquivo .sqlite" << endl;
    return 0;
}