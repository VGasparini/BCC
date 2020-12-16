# T1 - Processos e Threads

## Questão 1
Considere um programa concorrente com três threads A, B e C, mostradas no pseudocódigo abaixo.
Deseja-se que a sequência de execução seja tal que o  programa imprima para toda a eternidade (ou enquanto o programa executar) as mensagens `"CASO!\n"` ou `"CAOS!\n"`, dependendo da sequência de escalonamento (ou seja, em cada linha da saída as duas palavras devem ser igualmente possíveis). 

```C
void A(){
    while(1){
        printf("O");
    }
}

void B(){
    while(1){
        printf("CA");
        printf("!\n");
    }
}

void C(){
    while(1){
        printf("S");
    }
}
```

Para compilar e testar:

```bash
$ gcc ex1.c -o ex1 -pthread ; for i in {1..1000} ; do ./ex1 ; done > log ; sort < log | uniq -c
```

***

## Questão 2

1. O programa recebe três parâmetros $m, n, r$ na linha de comando; ou seja, o programa deve ser invocado como
```bash
$ ./prog m n r
```
> Adicionei um parâmetro a mais, caso informe 1 após a quantia de repetições é ativado o modo debbuging e várias informações das execuções são exibidas na tela

2. O programa deve alocar dinamicamente uma matriz $A_{m,n}$ números inteiros, onde $m$ é o número de linhas e $n$ é o número de colunas, e preenchê-la com números entre $1$ e $m × n$. Os números devem estar em posições aleatórias. Por exemplo, para $m = 2$ e $n = 3$, a matriz abaixo seria válida:
$$ \begin{pmatrix}
5 & 2 & 1\\
6 & 3 & 4
\end{pmatrix} $$

3. O programa deve criar quatro threads, todas elas executando a mesma função.

4. Cada thread deve receber como parâmetros, pelo menos, o seu número de identificação (de 1 a 4) e um outro parâmetro que permita determinar o ponto inicial de busca. Podem ser passados quaisquer parâmetros adicionais, conforme a necessidade.

5. O programa deve realizar $r$ rodadas do seguinte procedimento:
    1. `main()` escolhe um número aleatório entre $1$ e $m × n$;
    2. As threads buscam (em paralelo) o número sorteado na matriz;
    3. A primeira thread a encontrar o número é considerada a vencedora da rodada.

6. Cada thread deve buscar o número sorteado por main() partindo de um canto diferente da matriz ($a_{1,1}, a_{1,n}, a_{m,1}, a_{m,n}$) e percorrendo todos os elementos até encontrar o número procurado. Como a
matriz contém todos os números entre $1$ e $m × n$, o número sorteado sempre será encontrado.

7. Todas as threads devem iniciar a busca ao mesmo tempo, depois que o número for sorteado por `main()`.

8. A primeira thread que encontrar o número deve inserir o seu número de identificação em uma lista com a vencedora de cada rodada (i.e., o $k$-ésimo elemento da lista será a thread mais rápida da $k$-ésima rodada). Essa lista pode ser estática ou dinâmica.

9. Depois de encontrar o número sorteado, uma thread deve bloquear até que outro número seja sorteado, ou, se for a última rodada, até que a última thread termine o seu processamento. Em outras palavras, uma thread só pode passar para a próxima rodada (ou finalizar) quando todas as threads tiverem concluído a busca. O programa principal (`main()`) deve esperar que todas as threads terminem a rodada $k$ antes de avançar para a rodada $k + 1$.

10. Ao final das $r$ rodadas, o programa principal deve mostrar o número de rodadas em que cada thread foi a mais rápida, e declarar a(s) vencedora(s).

11. O programa deve tratar condições de disputa no código.
O exemplo a seguir ilustra o formato esperado para a saída do programa (invocado com $m = 30$, $n = 40$ e $r = 10$) quando as threads 1 e 3 foram as mais rápidas em duas rodadas cada uma, e as threads 2 e 4 foram mais rápidas em três rodadas cada.

```bash
$ ./prog 30 40 10
thread 1 =>  2 vitorias
thread 2 =>  3 vitorias
thread 3 =>  2 vitorias
thread 4 =>  3 vitorias
-------------------------------
Thread(s) vencedora(s): 2 4
```