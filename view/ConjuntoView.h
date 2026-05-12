#ifndef CONJUNTOVIEW_H
#define CONJUNTOVIEW_H

#include <QTextStream>
#include "Pagina.h"
#include "model/RoupaConjuntoModel.h"
#include "dao/RoupaConjuntoDao.h"

// página responsável pela visualização e gerenciamento de conjuntos
class ConjuntoView : public Pagina
{
public:
    ConjuntoView() : Pagina() {}
    ~ConjuntoView() {}

    // carrega a página principal de conjuntos com listagem e menu de ações
    void load();

private:
    // lista de conjuntos carregada do banco a cada exibição
    QList<RoupaConjuntoModel*> listaConjuntos;
    // objeto de acesso ao banco para conjuntos
    RoupaConjuntoDao conjDao;

    // responsável pelo cadastro (isEdicao=false) e edição (isEdicao=true)
    void form(bool isEdicao);
    // verifica se um campo está vazio e repede enquanto estiver
    void validarVazio(QString campo);
    // pede um ID ao usuário e retorna o conjunto correspondente do banco
    RoupaConjuntoModel* validarId();
    // exibe mensagem de "pressione Enter" e aguarda antes de voltar
    void retornar();
    // permite aumentar ou diminuir o estoque de um conjunto pelo ID
    void gerenciarEstoque();
    // remove um conjunto do banco pelo ID com confirmação
    void remover();
};

#endif // CONJUNTOVIEW_H