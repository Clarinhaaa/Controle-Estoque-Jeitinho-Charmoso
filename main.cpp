#ifdef _WIN32
#include <windows.h>
#endif

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include "PaginaInicial.h"
#include <QSqlQuery>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    #ifdef _WIN32
        // Configura a saída do terminal para UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    // Inicializando conexão com o banco de dados
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sqlite_database");
    if (!db.open()) {
        qDebug() << db.lastError().text();
        return -1;
    }
    QSqlQuery setupQuery;
    setupQuery.exec("DROP TABLE IF EXISTS Roupa"); // Apaga a tabela velha

    setupQuery.exec("CREATE TABLE Roupa ("
                    "id_roupa INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "nome_roupa TEXT, "
                    "tipo_roupa TEXT, "
                    "tamanho_roupa TEXT, "
                    "estoque_roupa INTEGER, "
                    "custo_roupa REAL, "
                    "preco_roupa REAL, "
                    "id_conjunto INTEGER)");

    setupQuery.exec("CREATE TABLE IF NOT EXISTS Conjunto ("
                    "id_conjunto INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "nome_conjunto TEXT)");

    // Loop principal
    PaginaInicial pagInicial;
    pagInicial.load();

    // Quando o usuário decide sair da aplicação
    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    return 0;
}
