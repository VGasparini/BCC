# Polinômio Interpolador

## Polinômio de Lagrange

p(x) = L1(x)y1 + L2(x)y2 + L3(x)y3...

Lk(x) = produtorio com j=1 e j!=k até n+1 {(x-xj) / (xk - xj)}

## Método das diferenças divididas

x  y
   a0               a1              a2                      a3                          a4
1 (2)|-3-2 / 2-1 =(-5)   7--5/3-1 = (6)    -4.5-6/4-1   = (-10.5/3)   2--10.5/3/5-1 = (1.375)
2 -3 |4--3 / 3-2 =  7    -2-7/4-2 = -4.5   1.5--4.5/5-2 = 2
3  4 |2-4 / 4-3  = -2    1--2/5-3 = 1.5
4  2 |3-2 / 5-4  =  1
5  3 |