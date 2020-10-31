#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <limits.h>
#include <time.h>

using namespace std;

vector<vector<int>> graph;
vector<vector<pair<int,float>>> graph_pesado;
vector<int> dfs_path;
vector<int> bfs_path;
vector<vector<int>> dij_path;


void edge(int a, int b);
void edge_pesado(int a, int b, float p);
void inicializa_grafo(int n);
void inicializa_grafo_pesado(int n);


void DFS(int v, bool visited[]){
    visited[v] = true;

    // cout << f << " ";
    dfs_path.push_back(v);

    for (auto i = graph[v].begin(); i != graph[v].end(); ++i) {
        if (visited[*i] == false)
            DFS(*i, visited);
    }
}

void BFS(int u, bool visited[]) {
    queue<int> q;

    q.push(u);
    visited[u] = true;

    while (!q.empty()) {
        int f = q.front();
        q.pop();

        // cout << f << " ";
        bfs_path.push_back(f);

        for (auto i = graph[f].begin(); i != graph[f].end(); ++i) {
            if (visited[*i] == false) {
                q.push(*i);
                visited[*i] = true;
            }
        }
    }
}

void DIJSKTRA(int v,float dist[]) {
    priority_queue<pair<float,int>,vector<pair<float,int>>,greater<pair<float,int>>> pq;
    
    pq.push(pair<float,int>(0,v));
    dist[v] = 0;

    while(!pq.empty()){
        pair<float, int> t = pq.top();
        pq.pop();
        for(pair<int,float> w : graph_pesado[t.second]){
            float c = t.first + w.second;
            if (dist[w.first] > c) {
                dist[w.first] = c;
                pq.push(pair<float, int>(c, w.first));
                dij_path[w.first].push_back(t.second);
            }
        }
    }
}


int main() {
    srand(time(nullptr));
    int n; 
    cin >> n; 

    bool visited[n];
    graph.assign(n, vector<int>());
    graph_pesado.assign(n, vector<pair<int,float>>());
    float dist[n];
    for (int i = 0; i < n; i++) dist[i] = INT_MAX ;
    int raiz = 0 + rand() % n;

    inicializa_grafo(n);

    cout << "BFS\nRaiz:" << raiz << "\n------\n";
    for (int i = 0; i < n; i++) visited[i] = false;
    BFS(raiz,visited);
    for (int i : bfs_path){
        if(i != raiz) cout << "->" << i ;
        else cout << "raiz";
    }

    cout << "\n\nDFS\nRaiz:" << raiz << "\n------\n";
    for (int i = 0; i < n; i++) visited[i] = false;
    DFS(raiz,visited);
    for (int i : dfs_path){
        if(i != raiz) cout << "->" << i ;
        else cout << "raiz";
    }


    inicializa_grafo_pesado(n);
    dij_path.assign(n, vector<int>());
    cout << "\n\nDijsktra\nRaiz:" << raiz << "\n------\n";
    DIJSKTRA(raiz, dist);
    for (int i = 0; i < n; i++){
        printf("Distancia %d ate %d = %4.4f | raiz",raiz,i,dist[i]);
        if (i!= raiz){
            for (auto j : dij_path[i]) cout << "->"<< j;
            printf("->%d\n", i);
        } else cout << endl;
        
    }
    return 0; 
}

// Utilidades

void inicializa_grafo(int n) {
    int t;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> t;
            if (t == 1)
                edge(i, j);
        }
    }
}

void inicializa_grafo_pesado(int n) {
    float p;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> p;
            if (p != -1) edge_pesado(i, j, p);
        }
    }
}

void edge_pesado(int a, int b, float p) {
    graph_pesado[a].push_back(pair<int,float>(b,p));
}

void edge(int a, int b) {
    graph[a].push_back(b);
}
