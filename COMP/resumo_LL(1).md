# Analisador Sintático LL(1)

* Só funciona para gramáticas não-ambiguas
* É de extrema importancia verificar se a gramática não possui recursividade a esquerda. Se tiver, tem que retirar

## Reconhecendo os Firsts e Follows

### First

FIRST(A) = primeiro terminal na regra A -> ...
Se o primeiro item não for terminal, então FIRST(A) = FIRST(B)

Ex:
```
A -> *AB
B -> CA
C -> e

FIRST(A) = { * }
FIRST(B) = FIRST(C) = { e }
FIRST(C) = { e }
```

### Follow

Iniciamos definindo que FOLLOW(S), sendo S a variavel inicial, como `FOLLOW(S) = { $ }`

Agora, para cada regra temos:
* Produções do tipo B -> aAb, sendo b um terminal ou variavel

```
FOLLOW(A) = FIRST(b)

Ex:

S -> A
A -> *AB
B -> /

FIRST(S) = { * }
FIRST(A) = { * }
FIRST(B) = { / }
FOLLOW(S) = { $ }
FOLLOW(A) = FIRST(B) = { / }
```
* Produções do tipo B -> aA ou B -> aAb onde b = e

```
FOLLOW(A) = FOLLOW(B)

Ex:

S -> (A) | e
A -> TE
E -> &TE | e
T -> (A) | a | b | c
FIRST(S) = { ( , e }
FIRST(A) = { ( , a , b , c } 
FIRST(E) = { & , e }
FIRST(T) = { ( , a , b , c }
FOLLOW(S) = { $ }
FOLLOW(E) = FOLLOW(A) = { ) }
FOLLOW(T) = FIRST(E) = { & } U FOLLOW(E) = { & , ) } <- Sem epsilon
FOLLOW(A) = FIRST()) = { ) }
```

## Tabela LL(1)

### Montagem

Para cada produção, inserir a produção nos terminais de FIRST da variavel mais a esquerda
Se for terminal, insere a produção no terminal
Se for produção indo pra epsilon, olhar para FOLLOW da variavel

| terminais-> variaveis   	        | a | b | c | ( | ) | & | # |
|:-----------------------------------:	|---|---|---|---|---|---|---|
| S                                   	|   |   |   |S->(A)|   |   |S->e|
| A                                   	|A -> TE|A -> TE|A -> TE|A -> TE|   |   |   |
| E                                   	|   |   |   |   |E -> e|E -> &TE|   |
| T                                   	|T -> a|T -> b|T -> c|T -> (A)|   |   |   |

## Reconhecer
Passo a passo
```
Empilhar variavel inicial
Olhar para o topo e para o inicio da palavra
Se forem iguais, desempilha e avança na palavra
Se for variavel, desempilha e empilha VARIAVELxCARACTERE

É aceito se chegar ao fim da palavra com a pilha vazia
```
Ex `input = (a&b)`

Pilha  |   Palavra |   Ação
---
```
S$        (a&b)$     S->(A)
(A)$      (a&b)$     Match, desempilha e avança
A)$       a&b)$      A -> TE
TE)$      a&b)$      T -> a        <---------- vc errou aqui
aE)$     a&b)$      Match, desempilha e avança
E)$      &b)$       T -> deu merda, vou reprovar
&TE)$    &b)$
TE)$     b)$
bE)$     b)$
E)$      )$
)$       )$
$        $
```
