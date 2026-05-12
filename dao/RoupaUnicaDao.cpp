#include "RoupaUnicaDao.h"

RoupaUnicaDao::RoupaUnicaDao() {}

bool RoupaUnicaDao::insert(RoupaUnicaModel &roupa) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen() && !db.open()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO Roupa (nome_roupa, tipo_roupa, tamanho_roupa, estoque_roupa, custo_roupa) "
                  "VALUES (:nome, :tipo, :tamanho, :estoque, :custo)");

    query.bindValue(":nome", roupa.getNome());
    query.bindValue(":tipo", roupa.getTipo());
    query.bindValue(":tamanho", roupa.getTamanho());
    query.bindValue(":estoque", roupa.getEstoque());
    query.bindValue(":custo", roupa.getCusto());

    if (!query.exec()) {
        qDebug() << "Erro SQLite:" << query.lastError().text();
        return false;
    }
    return true;
}
