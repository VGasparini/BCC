# Atividade Avaliativa

## Descrição

PHP + MYSQL: Cadastro utilizando formulário HTML + JS de **Gerenciador de Despesas**

Crie um formulário para realização de um cadastro (tente usar todos os tipos de campos), realizar as operações para:

- Inserir despesas;
- Mostrar despesas cadastradas;

Fazer também as validações adequadas.

## Como executar

Foi utilizado um container Docker para servir a infrastrutura do MySql, um para hospedar um servidor Apache e mais um container para phpmyadmin.

Para sincronizar esses diferentes ambientes, rodar a migration do banco e subir a aplicação bastante

```
docker-compose build
```

### Iniciando a aplicação

```
docker-compose up
```

É possivel utilizar o phpmyadmin em [http://localhost:8000](http://localhost:8000)
Enquanto a aplicação roda em [http://localhost:8001](http://localhost:8001)
