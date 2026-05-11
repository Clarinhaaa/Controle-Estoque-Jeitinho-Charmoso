#ifdef _WIN32
#include <windows.h>
#endif

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include "PaginaInicial.h"

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

    // Loop principal
    PaginaInicial pagInicial;
    pagInicial.load();

    // Quando o usuário decide sair da aplicação
    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    return 0;
}
