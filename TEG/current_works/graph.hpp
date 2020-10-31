#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
	int d, w;

	Edge() {
		this->d = -1;
		this->w = -1;
	}
	Edge(int dest, int weight=1) {
		this->d = dest;
		this->w = weight;
	}
};

class Graph {
public:
	int n_nodes;
	vector<vector<Edge>> edges;
	bool directed;

	Graph(int nodes, bool directed) {
		this->n_nodes = nodes;
		edges.assign(nodes, vector<Edge>());
		this->directed = directed;
	}

	int size(){
		return edges.size();
	}

	void add_edge(int origin, int dest, int weight=1) {
		edges[origin].push_back(Edge(dest, weight));
		if (!directed) edges[dest].push_back(Edge(origin, weight));
	}

	void remove_edge(int u, int v) {
		for(int i = 0; i< edges[u].size(); i++)
			if(edges[u][i].d == v) edges[u][i].d = -1;
		if(!directed){
			for(int i = 0; i< edges[v].size(); i++)
				if(edges[v][i].d == u) edges[v][i].d = -1;
			}
	}

	void set_loops() {
		for (int i=0; i<n_nodes; i++) {
			this->add_edge(i, i);
		}
	}

	void show_adjacency_matrix() {
		cout << endl << "Matriz de Adjacencia" << endl << endl;
		vector<vector<int>> m;
		m.assign(n_nodes, vector<int>(n_nodes,0));
		for (int i=0; i<n_nodes; i++) {
			for (auto e:edges[i]){
				m[i][e.d] = e.w;
			}
			for (int j=0; j<n_nodes; j++) {
				cout << m[i][j] << " ";
			}
			cout << endl;
		}
	}

	void show_adjacency_list() {
		cout << endl << "Lista de Adjacencia" << endl << endl;
		for(auto u:edges){
			for(auto v:u)
				cout << v.d << " ";
			cout << endl;
		}
	}

	int vertex_degree(vector<Edge> v) {
		return v.size();
	}

	bool is_connected() {
    	bool visited[n_nodes] = {false};
		int i;
		for (i = 0; i < n_nodes; i++)
			if (edges[i].size() != 0)
				break;
		if (i == n_nodes)
			return true;

    	DFS(i, visited);

		for (i = 0; i < n_nodes; i++){
			if (visited[i] == false and edges[i].size() > 0) return false;
		}
		return true;
	}

	int is_eulerian() {
			/* The function returns one of the following answers
				0 --> If graph is not Eulerian
				1 --> If graph is Semi-Eulerian (has a Euler path)
				2 --> If graph is Eulerian (has a Euler cycle) */

			if (is_connected() == false)
				return 0;

			int odd = 0;
			for (auto vertex:edges){
				if (vertex_degree(vertex) & 1)
					odd++;
			}
			if (odd == 1 or odd > 2)
				return 0;
			else if (odd == 2)
				return  1;
			return 2;

	}

	void show_fleury() {
		cout << endl << "Caminho Euleriano" << endl << endl;
		int u = 0;
		for (int i = 0; i < n_nodes; i++) {
			if (edges[i].size() & 1){
				u = i;
				break;
			}
		}
		euler_path(u);
		cout << endl;
	}

	void euler_path(int u) {
		for (auto edge:edges[u]) {
			int v = edge.d;
			if (v != -1 and is_valid(u, v)) {
				cout << u << " -> " << v << " | ";
				remove_edge(u, v);
				euler_path(v);
			}
		}
	}

	bool is_valid(int u, int v) {
		int count = 0;
		for(auto edge:edges[u]){
			if(edge.d != -1){
				count++;
			}
		}
		if (count == 1)
			return true;
		for(auto edge:edges[u])
			if(edge.d == v) return is_bridge(u, v);
		return false;
	}

	bool is_bridge(int u, int v) {
		bool visited1[n_nodes] = {false};
		int c1 = DFS_count(u, visited1);
		remove_edge(u, v);
		bool visited2[n_nodes] = {false};
		int c2 = DFS_count(u, visited2);
		add_edge(u, v);

		return (c1 > c2) ? false : true;
	}

	void DFS(int root, bool visited[]) {
		visited[root] = true;
		for (auto edge:edges[root]){
			if (!visited[edge.d])
				DFS(edge.d, visited);
		}
	}

	void DFS_path(int root, bool visited[], bool head=true) {
		if (head) cout << endl << "Ordem de visita DFS" << endl << endl<< "Raiz -> ";
		visited[root] = true;
		cout << root;
		for (auto edge:edges[root]){
			if (!visited[edge.d]){
				cout << " -> ";
				DFS_path(edge.d, visited, false);
			}
		}
	}

	int DFS_count(int root, bool visited[]) {
		visited[root] = true;
		int count = 1;
		for (auto edge:edges[root]){
			if (!visited[edge.d] and edge.d != -1)
				count += DFS_count(edge.d, visited);
		}
		return count;
	}

	void BFS_path(int root) {
		cout << endl << endl << "Ordem de visita BFS" << endl << endl;
		bool visited[this->size()] = {false};
		queue<int> queue; 
    	visited[root] = true; 
    	queue.push(root);
    	cout << "Raiz";
	    while(!queue.empty()) { 
	        root = queue.front();
        	queue.pop();
	        for (auto adj:edges[root]) { 
            	if (!visited[adj.d]) {
                	visited[adj.d] = true; 
                	queue.push(adj.d); 
            	} 
        	} 
        	cout << " -> " << root;
    	} 
    	cout << endl;
	}

	vector<int> dijk(int root) {

		queue<int> queue;
		vector<int> dist(n_nodes, INT_MAX);
		vector<int> visited(n_nodes, 0);

		dist[root] = 0;
		visited[root] = 1;
		queue.push(root);

		while (!queue.empty()) {

			int cur = queue.front();
			queue.pop();

			for (auto adj:edges[cur]) {
				dist[adj.d] = min(dist[adj.d], dist[cur]+adj.w);
				if (visited[adj.d] == 0) {
					visited[adj.d] = 1;
					queue.push(adj.d);
				}
			}

		}

		return dist;

	}
};

Graph * read_graph() {

	int nodes, directed;
	string s;
	cin >> nodes >> directed;
	getline(cin, s);
	Graph *g = new Graph(nodes, directed);

	for (int i=0; i<nodes; i++) {
		getline(cin, s);
		stringstream ss(s);
		int x;
		while (ss >> x) {
			if (x==-1) break;
			g->add_edge(i, x);
		}
	}

	return g;

}

Graph * read_weighted_graph() {

	int nodes, directed;
	string s;
	cin >> nodes >> directed;
	getline(cin, s);
	Graph *g = new Graph(nodes, directed);

	for (int i=0; i<nodes; i++) {
		getline(cin, s);
		stringstream ss(s);
		int x, w;
		while (ss >> x >> w) {
			if (x==-1) break;
			g->add_edge(i, x, w);
		}
	}

	return g;

}
