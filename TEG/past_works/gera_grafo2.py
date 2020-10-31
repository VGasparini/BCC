import random as r
from pprint import pprint
import math as m

def cria_ponto():
    return round(r.uniform(0,1),4)

def gera_x(n):
    x = set()
    while(len(x)<n):
        x.add(cria_ponto())
    return x

def gera_y(n):
    y = set()
    while(len(y)<n):
        y.add(cria_ponto())
    return y

def gera_coordenadas(n):
    pontos = []
    for x,y in zip(gera_x(n),gera_y(n)):
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

n = int(input())
vertices = gera_coordenadas(n)
grafo = gera_grafo(vertices)
grafo_pesado = pesa_grafo(grafo,vertices)

def DFS(s):
    global visitados,grafo,caminho
    visitados[s] = True
    caminho.append(s)
    for paraVisitar in range(len(grafo[s])):
        if grafo[s][paraVisitar] == 1 and paraVisitar not in caminho:
            DFS(paraVisitar)

visitados = [False for n in range(len(vertices))]
caminho = []
pprint(grafo)
print("Caminho:")
DFS(4)
print(*caminho)
print("Deu boa" if not False in visitados else "Fudeu")
