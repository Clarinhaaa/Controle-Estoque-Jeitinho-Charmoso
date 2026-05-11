#include <QCoreApplication>
#include <QtSql>
#include <iostream>
#include <string>

using namespace std;

// implementando o banco
void implementarBancoOficial() {
    QSqlQuery q;
    q.exec("PRAGMA foreign_keys = ON;");

    q.exec("CREATE TABLE IF NOT EXISTS Roupa ("
           "id_roupa INTEGER PRIMARY KEY AUTOINCREMENT, "
           "nome_roupa TEXT, "
           "estoque_roupa INTEGER, "
           "preco_roupa FLOAT)");

    // limpando e inserindo dados de teste para o alerta
    q.exec("DELETE FROM Roupa");
    q.exec("INSERT INTO Roupa (nome_roupa, estoque_roupa) VALUES ('Camisa Polo', 2)");  // ABAIXO
    q.exec("INSERT INTO Roupa (nome_roupa, estoque_roupa) VALUES ('Calca Jeans', 15)"); // OK
    q.exec("INSERT INTO Roupa (nome_roupa, estoque_roupa) VALUES ('Vestido Seda', 1)"); // ABAIXO

    cout << ">>> Banco implementado e dados de teste inseridos com sucesso!\n";
}

void verificarEstoqueBaixoRF022() {
    int limiteSeguranca = 5; // Valor padrão de segurança

    cout << "\n==========================================" << endl;
    cout << "       RELATORIO DE ESTOQUE BAIXO         " << endl;
    cout << "       (Limite de Seguranca: " << limiteSeguranca << ")         " << endl;
    cout << "==========================================" << endl;

    QSqlQuery query;
    query.prepare("SELECT nome_roupa, estoque_roupa FROM Roupa WHERE estoque_roupa <= :limite");
    query.bindValue(":limite", limiteSeguranca);

    if (!query.exec()) {
        cout << "Erro ao consultar o banco de dados!" << endl;
        return;
    }

    bool encontrouAlerta = false;
    while (query.next()) {
        encontrouAlerta = true;
        string nome = query.value(0).toString().toStdString();
        int qtd = query.value(1).toInt();

        cout << " [!!!] ALERTA DE ESTOQUE [!!!]" << endl;
        cout << " ITEM: " << nome << endl;
        cout << " QUANTIDADE ATUAL: " << qtd << endl;
        cout << " STATUS: Repor estoque imediatamente!" << endl;
        cout << "------------------------------------------" << endl;
    }

    if (!encontrouAlerta) {
        cout << " Todos os itens estao com estoque seguro. :)" << endl;
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("loja_estoque.sqlite");

    if (!db.open()) {
        cout << "Erro ao abrir o banco de dados!" << endl;
        return -1;
    }

    implementarBancoOficial();   // Passo 1
    verificarEstoqueBaixoRF022(); // Passo 2

    cout << "\nTeste concluido. Pressione Enter para fechar...";
    return 0;
}