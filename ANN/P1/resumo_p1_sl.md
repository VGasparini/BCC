# Sistemas Lineares

## Teste convergência

Se ||T|| < 1, então p(T) <= 1
Se  p(T) < 1, então converge

||T||inf = max entre todos (somatorio dos elementos em módulo de uma linha) para todas linhas

Iterações para convergência `k >= ln( ( ||x2|| - ||x1|| ) / E(1-||T||)) / ln(1 / ||T||)`

## Jacobi
```
A = L+D+U -> Matriz dos coeficientes do sistema
L -> Triangular inferior
D -> Diagonal principal    | D_ = 1/D
U -> Triangular superior
B = Matriz independente
```

`Xk+1 = -D'(L+U)Xk + D'B`

## Gauss-Seidel

`Xk+1 = -(L+D)'UXk + (L+D)'B`

# Sistemas não-lineares

Escrever o sistema como G(g1,g2)
Escrever a matriz G'|dg1/dx1 dg1/dx2|
                    |dg2/dx1 dg2/dx2|

`Xk+1 = Xk - inv(F'(Xk))*F(x=Xk)`
```
    A = |a b|
        |c d|

inv(A)= |d -b| * 1/det(a)
        |-c a|
```
