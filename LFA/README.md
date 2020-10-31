# LFA
> Formal languages and Automata

- Professor Ricardo Ferreira Martins
- 2019.1

## Simulando um fábrica de automóveis com automatos

### Preparando o ambiente:

Recomenda-se uso de um sistema Linux. Outra plataforma demanda outros procedimentos

1. Para instalar o Graphviz utilize os seguintes comandos
    1. `sudo apt-get install graphviz`
    2. `pip3 install graphviz`
        
2. Para executar o simulador utilize os seguintes comandos (na pasta raiz do código)
    1. `python3 main.py`

3. Uso do simulador
    1. As instruções de uso estão claras por meio de mensagens na tela.
    2. Para modificar algumas configurações de execução
        abrir com um editor de texto o arquivo main.py
    3. Para modificar o automato de validação
        abrir com um editor de texto o arquivo valida_demanda.txt
    4. Para modificar os automatos de produção
        abrir com um editor de texto o arquivo respectivo da linha.
        Ex: b.txt se refere a linha Bozzola
        
4. Exemplo de uso
    1. `python3 main.py`
    2. Inserindo demanda: `bL@;gB#;`
        * 2 carros, um do tipo Bozzola e um do tipo Gasparini
    3. Digitando `a` para acompanhar passo a passo
    4. Digitando `s` para acompanhar as entradas nas linhas
        * É mostrado o primeiro carro entrando na sua linha
    5. Digitando novamente `a` para avançar (ou `f` para acelerar ao final)
    6. Mostrado as estatisticas de produção
    7. Digitando `s` para olhar as fitas
    8. Finalizado o simulador
        * Durante todo instante é possivel vizualizar os avanços por meio de PDFs na pasta `saida`
