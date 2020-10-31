from random import randrange as rand


def generate(n, num):
    primos = set()
    num += 1
    while(len(primos) < n):
        num += 2
        for i in range(2, num):
            if (num % i) == 0:
                break
        else:
            primos.add(num)
    return list(primos)


def witness(a, s, d, n):
    x = pow(a, d, n)        # exponenciacao modular para evitar big int
    if x == 1:
        return True
    for i in range(s - 1):
        if x == n - 1:
            return True
        x = pow(x, 2, n)
    return x == n - 1


def miller_rabin(n, k):
    if n == 2:
        return True
    if not n & 1:
        return False

    s = 0
    d = n - 1

    while d % 2 == 0:
        d >>= 1
        s += 1

    for i in range(k):
        a = rand(2, n - 1)
        if not witness(a, s, d, n):
            return False
    return True


S = [rand(3, 100) for i in range(3)]

primos_base = generate(20, 10000)
nao_primos_base = [i for i in range(10000, 10000+2*20, 2)]
lista = primos_base + nao_primos_base


for s in S:
    primos_test = []
    nao_primos_test = []

    cont_p, cont_n, cont_e = 0, 0, 0
    for n in lista:
        if miller_rabin(n, s):
            primos_test.append(n)
        else:
            nao_primos_test.append(n)

    for p in primos_test:
        if p in primos_base:
            cont_p += 1

    for n in nao_primos_test:
        if n in nao_primos_base:
            cont_n += 1
        elif n in primos_base:
            cont_e += 1
    print()
    print("Primos identificados corretamente", cont_p)
    print("Nao-primos identificados corretamente", cont_n)
    print("Erros", cont_e)
    print("Base usada:", s)
