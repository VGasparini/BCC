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

def gera_grafo(vertices,v):
    arestas = set()
    while len(arestas) < m.ceil(v*(v-1)/3):                                         #gerando aleatoriamente (v*(v-1)/3 arestas, arredondando para o maior inteiro
        v1,v2 = r.randrange(v),r.randrange(v)
        if v1 != v2:                                                                #garantindo que não exista aresta para o próprio vértice
            arestas.add((v1,v2))
    grafo = [[0 for m in range(v)] for n in range(v)]                               #iniciando grafo[n][m] = 0
    for de,para in arestas:                                                         #ligando arestas
        grafo[de][para] = 1                                           
        grafo[para][de] = 1
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
grafo = gera_grafo(vertices,n)
grafo_pesado = pesa_grafo(grafo,vertices)

pprint(grafo)
pprint(grafo_pesado)
