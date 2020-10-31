/* ################################################
	Autores: Vinicius Gasparini e Filipe Cattoni
	Nome: Algoritmo de Fleury
   ################################################ */

#include <bits/stdc++.h>
#include "./graph.hpp"
using namespace std;

int main() {
	Graph *g = read_graph();
	g->show_adjacency_matrix();
	g->show_adjacency_list();
	if(g->is_connected()){
		int ans = g->is_eulerian();
		if (ans == 0){
			cout << "Tipo: Nao Euleriano" << endl;
		} else if (ans == 1) {
			cout << endl << "Tipo: Semi-Euleriano";
			g->show_fleury();
		} else {
			cout << endl << "Tipo: Euleriano";
			g->show_fleury();
		}
	} else {
		cout << "Eh desconexo";
	}
}
