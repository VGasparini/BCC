from math import tan
"""
Funcionamento
    O algoritmo implementado funciona da seguinte maneira
    É necessário definir a função, os intervalos inferioes e superiores e por fim
    quantidade de iterações

    a = limite inferior
    b = limite superior
    n = iterações
    f(x) = função
"""

def calcula_integral(f, a, b, n):
    h = (b-a)/n
    s = (f(a) + f(b))/2
    for i in range(1, n):
        s += f(a + i*h)
    return h*s

def f(x):
    res = x+tan(tan(abs(1/4*x - 7/4))) #alterar funcao
    return res

a = 3
b = 11
n = 19
resultado = calcula_integral(f, a, b, n)
print('Integral de f(x) = FUNCAO_AQUI, de %d até %d' % (a,b))
print('I ~ %.2f' % resultado)
print('%d Iterações' % n)