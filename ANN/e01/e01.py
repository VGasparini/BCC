#########################
#   Vinicius Gasparini  #
#    Análise Numérica   #
#      Exercicio 01     #
#########################

def f(x):
    return x**5-4*x-3

def verificacao_bolzano(a,b):
    print("*** Verificação Bolzano ***")
    fa = f(a)
    fb = f(b)
    print("f(a)= %.4f\nf(b)= %.4f"%(fa,fb))
    if f(a)*f(b) < 0:
        print("Como a f(a)*f(b) < 0 ∃ x | f(x) = 0")
        return True
    print("Como a f(a)*f(b) >= 0 ∄ x | f(x) = 0")
    return False

    
def bissecao(a,b,max_iter):
    print("\n*** Método da Bisseção ***")
    print("Procurando uma raiz no intervalo [%.3f,%.3f]"%(a,b))
    print("Iteração | (x , y)")
    fa = f(a)
    for i in range(max_iter):
        p = a + (b-a)/2  
        print("%d | ( %.6f , %.6f )"%(i+1,p,f(p)))
        fp = f(p)  
        if (fa * fp > 0):  
            a = p  
            fa = fp  
        else:  
            b = p
    return p


def bissecao2(a,b,epsilon):
    cont = 1
    fa = f(a)
    while((b-a)/2 >= epsilon):
        p = a + (b-a)/2  
        fp = f(p)  
        if (fa * fp > 0):  
            a = p  
            fa = fp  
        else:  
            b = p
        cont += 1  
    return cont


a = 0.646
b = 2.431
max_iter = 8
epsilon = 10**(-14)


if __name__ == "__main__":
    if verificacao_bolzano(a,b):
        raiz = bissecao(a,b,max_iter)
        cont = bissecao2(a,b,epsilon)
        print("\nRaiz encontrada após %d iterações = %.6f"%(max_iter,raiz))
        print("Iterações para erro menor que 10e-14 = %d"%cont)
    
    else:
        print("O intervalo não possui raiz")
