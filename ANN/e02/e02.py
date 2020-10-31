def f(x):
    return x**3-4*x-1

def f_(x):
    return 3*(x**2)-4

def bolzano(a,b):
    if (f(a)*f(b)) < 0:
        return True
    return False

def newton(p,n):
    for i in range(n):
        p = p-(f(p)/f_(p))
    return p

def secantes(pontos,n):
    for i in range(1,n-1):
        pontos.append((pontos[i-1]*f(pontos[i]) - pontos[i]* f(pontos[i-1]))
                        /(f(pontos[i]) - f(pontos[i-1])))
    return pontos[-1]

def posicao_falsa(p0,p1,n):
    if bolzano(p0,p1):
        p3=p0 - f(p0)*(p1-p0)/(f(p1)-f(p0))
        for i in range(n):
            if bolzano(p0,p3):
                p0=p3
            else:
                p1=p3
            p3=p0 - f(p0)*(p1-p0)/(f(p1)-f(p0))
        return p3
    else:
        print("Reprovado no teorema de Bolzano")

# Questao 1
p = float(input("Informe o p0: "))
n = int(input("Informe a quantidade de iterações: "))
ans = newton(p,n)
print("{:.8}".format(ans))

# Questao 2
p0 = float(input("Informe o p0: "))
p1 = float(input("Informe o p1: "))
n = int(input("Informe a quantidade de iterações: "))
pontos = [p0,p1]
ans = secantes(pontos,n)
print("{:.7}".format(ans))

# Questao 3
p0 = float(input("Informe o p0: "))
p1 = float(input("Informe o p1: "))
n = int(input("Informe a quantidade de iterações: "))
ans = posicao_falsa(p0,p1,n)
print("{:.7}".format(ans))

