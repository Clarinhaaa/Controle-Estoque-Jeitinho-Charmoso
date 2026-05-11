# Controle de Estoque da Jeitinho Charmoso
Sistema responsável por gerenciar o estoque das roupas vendidas pela loja Jeitinho Charmoso, além dos tecidos comprados para a sua produção. Desenvolvido como projeto para a disciplina de Estrutura de Dados Orientada a Objetos do Centro de Informática (UFPE).

---

## Arquitetura do projeto
Ela foi baseada em um sistema Model-View, dividida em 3 subspastas:

```
controle-estoque-jeitinho-charmoso/
├── controle-estoque-jeitinho-charmoso.pro
├── dao/
│   ├── dao.pri
│   ├── Headers/
│   ├── Sources/
├── model/
│   ├── model.pri
│   ├── Headers/
│   ├── Sources/
├── view/
│   ├── view.pri
│   ├── Headers/
│   ├── Sources/
├── Headers/
├── Sources/
└── Other files/
```

---

## Padrões de código
- Todas as classes em `/View` são herdadas da classe abstrata `Pagina.h`, localizada no diretório raiz do projeto.

- Além disso, essa classe possui 2 atributos do tipo `QTextStream`, um para input e o outro, output. Esse tipo foi desenvolvido pelo próprio Qt para lidar com as `QStrings`, substituindo as `strings`, `cin` e `cout` do namespace `std`.
