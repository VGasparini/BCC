/* ################################################
	Autores: Vinicius Gasparini e Filipe Cattoni
	Nome: Algoritmo de DFS
   ################################################ */

#include <bits/stdc++.h>
#include "./graph.hpp"
using namespace std;

int main() {
	Graph *g = read_graph();
	g->show_adjacency_matrix();
	g->show_adjacency_list();

	bool visited[g->size()] = {false};

	g->DFS_path(0,visited);
	g->BFS_path(0);
}
