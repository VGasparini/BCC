/* ################################################
	Autores: Vinicius Gasparini e Filipe Cattoni
	Nome: Algoritmo de Dijkstra
   ################################################ */

#include <bits/stdc++.h>
#include "./graph.hpp"
using namespace std;

int main() {
	Graph *g = read_weighted_graph();
	g->show_adjacency_matrix();
	g->show_adjacency_list();

	vector<int> dist;

	dist = g->dijk(0);
	cout << endl << "Raiz: 0 " << endl << "Distancias: " << endl;
	for (auto i:dist) {
		cout << i << " ";
	}
	cout << endl;
}
