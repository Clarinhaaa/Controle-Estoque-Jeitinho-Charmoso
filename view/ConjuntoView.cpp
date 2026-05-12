#include "ConjuntoView.h"
#include "RoupaDao.h"
#include "ConjuntoDao.h"
#include "RoupaView.h"
#include <QStringList>
#include <utility>

ConjuntoView::ConjuntoView() {}

void ConjuntoView::cadastrarConjunto() {
    out << "\033[H\033[J";
    out << "=== MONTAGEM DE CONJUNTO ===\n\n";

    RoupaDao roupaDao;
    QList<RoupaModel*> todas = roupaDao.getAll();
    QList<RoupaModel*> disponiveis;

    // Filtra apenas as roupas que são "Conjunto"
    for (RoupaModel* r : std::as_const(todas)) {
        if (r->getTipo() == "Conjunto") {
            disponiveis.append(r);
        }
    }

    // Se não tiver peça de conjunto, avisa e dá a opção de cadastrar
    if (disponiveis.isEmpty()) {
        out << "[AVISO] Nenhuma 'Peca de Conjunto' encontrada no estoque!\n";
        out << "Voce precisa cadastrar pecas avulsas antes de montar um look completo.\n\n";
        out << "[1] Ir para Cadastro de Roupas\n";
        out << "[2] Voltar\n";
        out.flush();

        if (in.readLine().toInt() == 1) {
            RoupaView rv;
            rv.load(); // Pula para a tela de roupas
        }
        qDeleteAll(todas);
        return;
    }

    // Nome Obrigatório
    QString nomeConjunto;
    while (nomeConjunto.trimmed().isEmpty()) {
        out << "Nome do Conjunto: "; out.flush();
        nomeConjunto = in.readLine();

        if (nomeConjunto.trimmed().isEmpty()) {
            out << "[ERRO] O nome do conjunto e obrigatorio!\n";
        }
    }

    // Simula um dropdown e peças são obrigatórias
    out << "\nPecas Disponiveis:\n";
    for (RoupaModel* r : std::as_const(disponiveis)) {
        out << "ID: " << r->getId() << " | " << r->getNome() << " (Tam: " << r->getTamanho() << ")\n";
    }

    QStringList idsStr;
    QList<int> idsPecas;

    while (idsPecas.isEmpty()) {
        out << "\nDigite os IDs das pecas que formam esse conjunto (separados por espaco): "; out.flush();
        idsStr = in.readLine().split(" ");

        for(const QString& s : idsStr) {
            if (!s.trimmed().isEmpty()) {
                idsPecas.append(s.toInt());
            }
        }

        if (idsPecas.isEmpty()) {
            out << "[ERRO] Voce precisa selecionar pelo menos uma peca!\n";
        }
    }

    ConjuntoDao conjuntoDao;
    int novoId = conjuntoDao.insert(nomeConjunto);

    if (novoId != -1 && conjuntoDao.vincularPecas(novoId, idsPecas)) {
        out << "\n[SUCESSO] Conjunto '" << nomeConjunto << "' (ID: " << novoId << ") criado com sucesso!\n";
    } else {
        out << "\n[ERRO] Falha ao processar o conjunto no banco de dados.\n";
    }

    qDeleteAll(todas); // Limpa a memória

    out << "\nPressione Enter para continuar..."; out.flush();
    in.readLine();
}