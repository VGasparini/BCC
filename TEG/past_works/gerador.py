import random as r
import math as m

def cria_ponto():
    return round(r.uniform(0,1),4)

def gera_coordenadas(n):
    pontos = []
    set_x,set_y = set(),set()
    while(len(set_x)<n):
        set_x.add(cria_ponto())
    while(len(set_y)<n):
        set_y.add(cria_ponto())
    for x,y in zip(set_x,set_y):
        pontos.append((x,y))
    return pontos

def gera_grafo(vertices):
    grafo = [[0 for m in range(len(vertices))] for n in range(len(vertices))]       #compressão de lista para criar a matriz grafo[n][m] com todos os valores 0
    for vertice in range(len(vertices)):                                            #iteração até n
        arestas = set()
        while len(arestas) <= 2:
            aresta = r.randrange(len(vertices))
            if aresta != vertice: arestas.add(aresta)                               #gera 3 arestas aleatórias
        for aresta in arestas:                                                      #itera entre esses 3 valores
            if vertice!=aresta:                                                     #garantindo vértice não possui aresta para si 
                grafo[vertice][aresta] = 1                                          #garantindo grafo não-dirigido
                grafo[aresta][vertice] = 1                                          #garantindo grafo não-dirigido
    return grafo 

def pesa_grafo(grafo,vertices):
    grafo_pesado = [[-1 for m in range(len(grafo))] for n in range(len(grafo))]     #compressão de lista para criar a matriz grafo_pesado[n][m] com todos os valores -1
    for n in range(len(grafo)):                                                     #iteração até n
        for m in range(len(grafo[n])):                                              #iteração até m
            if grafo[n][m] == 1:                                                                    
                dist = distancia(vertices[m],vertices[n])                           #calculando distancia entre os dois vertices
                grafo_pesado[m][n] = dist                                           #garantindo grafo não-dirigido
                grafo_pesado[n][m] = dist                                           #garantindo grafo não-dirigido
    return grafo_pesado

def distancia(p1,p2):
    return float(str(m.sqrt((p2[0]-p1[0])**2 + (p2[1]-p1[1])**2))[:6])

def print_grafo(grafo,grafo_pesado,n):
    f  = open('grafo'+str(n)+'vertices', 'w')
    f.write(str(n)+'\n')
    for v in grafo:
        f.writelines(''.join(str(v)).replace('[','').replace(']','').replace(',','')+'\n')
    for v in grafo_pesado:
        f.writelines(''.join(str(v)).replace('[','').replace(']','').replace(',','')+'\n')
        
def print_vestices(vertices,n):
    f  = open(str(n)+'vertices', 'w')
    f.write(str(n)+'\n')
    for v in vertices:
        f.writelines(str(v).replace('(','').replace(')','').replace(',','')+'\n')
        
print("Digite os tamanhos de grafos a gerar (espaçados)")
l = list(map(int,input().split()))
for n in l:
    vertices = gera_coordenadas(n)
    grafo = gera_grafo(vertices)
    grafo_pesado = pesa_grafo(grafo,vertices)
    print_grafo(grafo,grafo_pesado,n)
    print_vestices(vertices,n)