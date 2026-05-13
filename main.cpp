#ifdef _WIN32
#include <windows.h>
#endif

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include "PaginaInicial.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    a.setOrganizationName("JeitinhoCharmoso");
    a.setApplicationName("ControleEstoque");

    #ifdef _WIN32
        // Configura a saída do terminal para UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

        { // bloco para encerrar o banco corretamente
            // caminho onde o banco será salvo no deploy
            QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
            QDir dir(appDataPath);
            if (!dir.exists()) dir.mkpath(".");

            QString dbPath = dir.filePath("sqlite_database");
            if (!QFile::exists(dbPath)) { // se o arquivo não existir (primeira vez rodando), ele é copiado do .qrc para a pasta
                if (QFile::copy(":/sqlite_database", dbPath))
                    QFile::setPermissions(dbPath, QFileDevice::ReadOwner | QFileDevice::WriteOwner);
            }

            // inicializando conexão com o banco de dados
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(dbPath);
            if (!db.open()) {
                qDebug() << db.lastError().text();
                return -1;
            }

            // loop principal
            PaginaInicial pagInicial;
            pagInicial.load();

            // quando o usuário decide sair da aplicação
            db.close();
        }

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    return 0;
}