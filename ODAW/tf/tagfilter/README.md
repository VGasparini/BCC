# Tag Filter

Aplicação para acompanhamento de tags do Twitter

> Projeto desenvolvido como parte da avaliação para a disciplina de Desenvolvimento de Aplicações WEB

## Escopo

- Cadastrar e remover hashtags
- Coletar com frequência mensagens publicadas no Twitter contendo as hashtags (dentro do limite da API)
- Listar as mensagens coletadas mostrando: mensagem, autor, data de publicação
- Filtrar as mensagens listadas por hashtag
- Salvar e Recuperar as Tags sem necessidade de cadastro de usuário

## Instalação

- Clone este repositório
- Instale o `docker` e `docker-compose`
- Instale todas as dependências do projeto com `docker-compose build`
- Execute a criação do banco de dados através do comando `docker-compose exec web python manage.py create_db`
- Inicialize com o comando `docker-compose up`

## Configuração

- Para utilizar a aplicação é necessário criar um novo app para obter as credenciais de acesso a API. Para isso, acesse o link [Twitter Devolopers](https://developer.twitter.com/).
- Sob posse das credenciais do app, preencha o arquivo `.env.dev` ou `.env.prod`

## Testes

- Os testes automatizados foram desenvolvidos utilizando a biblioteca nativa [unittest](https://docs.python.org/3/library/unittest.html)
- Para realizar os testes execute `docker-compose exec web python test.py -v`
- A rotina de testes verifica:
  - Se o servidor está funcional
  - Se a aplicação inicia sem nenhuma tag
  - Se a inserção de tag funciona
  - Se a inserção de uma tag duplicada é tratada
  - Se a removação da tag funciona

## Deploy

- A aplicação está configurada em docker, então qualquer cloud com suporte a multiplos containers com `docker-compose`

## Documentação auxiliar

- [Twitter API reference](https://developer.twitter.com/en/docs/api-reference-index)
- [Flask](https://www.palletsprojects.com/p/flask/)

## Code formatting

Foi utilizado a ferramenta [Black](https://black.readthedocs.io/en/stable/) para a formatação do código.

## Licença

[MIT](https://choosealicense.com/licenses/mit/)
