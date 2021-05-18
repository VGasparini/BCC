import collections
import itertools
import random
from pprint import pprint

import graphviz

import time

################################################
#   Autores: Vinicius Gasparini e Filipe Cattoni
#   Nome: Arvore de Steiner
################################################

# Estruturas:
# Node: str
# Graph: {Node: set(Node)} lista de adjacencia
# Terminals: set(Node)
# Edge: frozenset([Node, Node]) set imutavel, para evitar operacoes indevidas
# Tree: set(Edge) lista de arestas
# Path: [Node]
# ShortestPath: {(Node, Node): Path}


def render_graph(dot, name):
    dot.format = "pdf"
    dot.render(name)


def get_edges_from_graph(g):
    edges = set()
    for v, es in g.items():
        for e in es:
            edges.add(frozenset((v, e)))
    return edges


def render_initial_graph(g, terminals):
    terminal_style = {"style": "filled", "fillcolor": "lightgrey"}
    normal_style = {"color": "black"}

    def get_steiner_nodes(terminals, graph):
        ns = set()
        for e0 in graph.keys():
            ns.add(e0)
        return ns - set(terminals)

    def get_node_style(v, terminals, steiner_nodes):
        if v in terminals:
            return terminal_style
        elif v in steiner_nodes:
            return normal_style
        return {}

    def get_edge_style(e, tree_edges):
        if e in tree_edges:
            return normal_style
        return {}

    dot = graphviz.Graph()
    steiner_nodes = get_steiner_nodes(terminals, g)
    for v, es in g.items():
        dot.node(v, **get_node_style(v, terminals, steiner_nodes))
    for v0, v1 in get_edges_from_graph(g):
        dot.edge(v0, v1, **get_edge_style(frozenset((v0, v1)), g))
    render_graph(dot, "initial_graph")


def render_steiner_solution(g, terminals, tree_edges):
    terminal_style = {"style": "filled", "fillcolor": "lightgrey"}
    steiner_style = {"color": "red"}
    steiner_edge = {"color": "red", "label": "1"}

    def get_steiner_nodes(terminals, tree_edges):
        ns = set()
        for e0, e1 in tree_edges:
            ns.add(e0)
            ns.add(e1)
        return ns - set(terminals)

    def get_node_style(v, terminals, steiner_nodes):
        if v in terminals:
            return terminal_style
        elif v in steiner_nodes:
            return steiner_style
        return {}

    def get_edge_style(e, tree_edges):
        if e in tree_edges:
            return steiner_edge
        return {}

    dot = graphviz.Graph()
    steiner_nodes = get_steiner_nodes(terminals, tree_edges)
    for v, es in g.items():
        dot.node(v, **get_node_style(v, terminals, steiner_nodes))
    for v0, v1 in get_edges_from_graph(g):
        dot.edge(v0, v1, **get_edge_style(frozenset((v0, v1)), tree_edges))
    render_graph(dot, "steiner_graph")


def create_random_graph(n, p):
    vs = [str(i) for i in range(n)]
    edge_count = int(round(p * (n - 1) * n / 2))
    es = sample_iterable(generate_all_possible_edges(vs), edge_count)
    g = {v: [] for v in vs}
    for v0, v1 in es:
        g[v0].append(v1)
        g[v1].append(v0)
    return connect_components(get_connected_components(g))


def get_connected_components(g):
    components = []
    unvisited = set(g)
    while unvisited:
        component = {}
        queue = collections.deque(random.sample(unvisited, 1))
        while queue:
            cur_node = queue.popleft()
            component[cur_node] = g[cur_node]
            if cur_node not in unvisited:
                continue
            for neighbor in g[cur_node]:
                if neighbor in unvisited:
                    queue.append(neighbor)
            unvisited.remove(cur_node)
        components.append(component)
    return components


def connect_components(gs):
    ret = {}
    for g in gs:
        ret.update(g)
    for g0, g1 in zip(gs, gs[1:]):
        v0 = random.sample(list(g0), 1)[0]
        v1 = random.sample(list(g1), 1)[0]
        ret[v0].append(v1)
        ret[v1].append(v0)
    return ret


def generate_all_possible_edges(vs):
    for i, v0 in enumerate(vs):
        for v1 in vs[i + 1 :]:
            yield (v0, v1)


def sample_iterable(iterable, samplesize):
    results = []
    iterator = iter(iterable)
    try:
        for _ in range(samplesize):
            results.append(next(iterator))
    except:
        pass
    random.shuffle(results)
    for i, v in enumerate(iterator, samplesize):
        r = random.randint(0, i)
        if r < samplesize:
            results[r] = v
    return results


def pick_random_terminals(g, n):
    return frozenset(random.sample(list(g), n))


def get_steiner_tree(g, Y):

    # Heuristica utilizada: Caminho mais curto com Busca local

    # Escolhendo um terminal qualquer
    q = random.sample(Y, 1)[0]
    # Guardando o subset de terminais sem o q
    # Definindo espaço de busca
    C = Y - {q}
    # Calculo o menor caminho de todos para todos
    # Complexidade O(V*E log V)
    dij = all_pairs_shortest_paths(g)
    # Gerando todos os casos base considerando como raiz um terminal
    # Propondo solução inicial (método construtivo de menor caminho)
    S = get_steiner_base_case(dij)
    SkD = {}
    length = len(Y) - 1
    for i in range(2, len(Y)):
        # Calculando as soluções
        # Inicia escolhendo dois terminais como base
        for Dtup in itertools.combinations(C, i):
            D = frozenset(Dtup)
            # Para cada vertice do grafo
            for k in g:
                E_and_F_trees = []
                # Gera a floresta enraizada em k com as respostas para cada k-subset
                # i.e subconjunto F que pertence ao conjunto E
                for E, F in algorithm_u(Dtup, 2):
                    E_and_F_trees.append((S[frozenset([k] + E)], S[frozenset([k] + F)]))
                # Guarda a melhor resposta da floresta
                # melhoria da solução com base na vizinhança
                SkD[(k, D)] = min(E_and_F_trees, key=lambda x: len(x[0]) + len(x[1]))
            # Caso a melhor resposta conter todos os terminais, calcula a resposta e guarda
            for m in {q} if D == C else g:
                lengths_and_k_and_tree = []
                for k in g:
                    # Encontrando uma solução ótima para o k-subset
                    # i.e ótimo local
                    lengths_and_k_and_tree.append(
                        (
                            len(dij[(m, k)])
                            + len(SkD[(k, D)][0])
                            + len(SkD[(k, D)][1]),
                            k,
                            node_and_path_to_edges(m, dij[(m, k)])
                            .union(SkD[(k, D)][0])
                            .union(SkD[(k, D)][1]),
                        )
                    )
                # Compara com a melhor resposta até agora e guarda tamanho, k-esimo iteracao(dp), arvore
                # i.e ótimo global
                length, k, tree = min(lengths_and_k_and_tree, key=lambda x: x[0])
                S[frozenset(D.union(frozenset([m])))] = tree
    # Retorna a melhor arvore encontra e o tamanho
    return S[frozenset(Y)], length


def node_and_path_to_edges(v, p):
    edges = [frozenset([e0, e1]) for e0, e1 in zip([v] + p, p)]
    return frozenset(edges)


def get_steiner_base_case(dij):
    b = {}
    for (v0, v1), p in dij.items():
        b[frozenset([v0, v1])] = node_and_path_to_edges(v0, p)
    return b


def all_pairs_shortest_paths(g):
    d = {}
    for v in g:
        d.update(single_source_shortest_paths(g, v))
    return d


def single_source_shortest_paths(g, s):
    d = {(s, v): [] for v in g}
    unvisited = set(g)
    queue = collections.deque([s])
    while queue:
        current = queue.popleft()
        if current not in unvisited:
            continue
        for neighbor in g[current]:
            if neighbor in unvisited:
                path = d[(s, current)]
                dist = len(path)
                neighbor_dist = len(d[(s, neighbor)])
                if dist + 1 < neighbor_dist or neighbor_dist == 0:
                    d[(s, neighbor)] = path + [neighbor]
                queue.append(neighbor)
        unvisited.remove(current)
    for v in unvisited:
        del d[(s, v)]
    return d


def algorithm_u(ns, m):
    # Algoritmo U de Knuth para k-subsets
    # Art of Computer Programming, Volume 4, Fascicle 3B
    # http://codereview.stackexchange.com/questions/1526/finding-all-k-subset-partitions
    def visit(n, a):
        ps = [[] for i in range(m)]
        for j in range(n):
            ps[a[j + 1]].append(ns[j])
        return ps

    def f(mu, nu, sigma, n, a):
        if mu == 2:
            yield visit(n, a)
        else:
            for v in f(mu - 1, nu - 1, (mu + sigma) % 2, n, a):
                yield v
        if nu == mu + 1:
            a[mu] = mu - 1
            yield visit(n, a)
            while a[nu] > 0:
                a[nu] = a[nu] - 1
                yield visit(n, a)
        elif nu > mu + 1:
            if (mu + sigma) % 2 == 1:
                a[nu - 1] = mu - 1
            else:
                a[mu] = mu - 1
            if (a[nu] + sigma) % 2 == 1:
                for v in b(mu, nu - 1, 0, n, a):
                    yield v
            else:
                for v in f(mu, nu - 1, 0, n, a):
                    yield v
            while a[nu] > 0:
                a[nu] = a[nu] - 1
                if (a[nu] + sigma) % 2 == 1:
                    for v in b(mu, nu - 1, 0, n, a):
                        yield v
                else:
                    for v in f(mu, nu - 1, 0, n, a):
                        yield v

    def b(mu, nu, sigma, n, a):
        if nu == mu + 1:
            while a[nu] < mu - 1:
                yield visit(n, a)
                a[nu] = a[nu] + 1
            yield visit(n, a)
            a[mu] = 0
        elif nu > mu + 1:
            if (a[nu] + sigma) % 2 == 1:
                for v in f(mu, nu - 1, 0, n, a):
                    yield v
            else:
                for v in b(mu, nu - 1, 0, n, a):
                    yield v
            while a[nu] < mu - 1:
                a[nu] = a[nu] + 1
                if (a[nu] + sigma) % 2 == 1:
                    for v in f(mu, nu - 1, 0, n, a):
                        yield v
                else:
                    for v in b(mu, nu - 1, 0, n, a):
                        yield v
            if (mu + sigma) % 2 == 1:
                a[nu - 1] = 0
            else:
                a[mu] = 0
        if mu == 2:
            yield visit(n, a)
        else:
            for v in b(mu - 1, nu - 1, (mu + sigma) % 2, n, a):
                yield v

    n = len(ns)
    a = [0] * (n + 1)
    for j in range(1, m + 1):
        a[n - m + j] = j - 1
    return f(m, n, 0, n, a)


def statistics(t1, t2, l):
    print("Tempo para criação aleatória do grafo: {:.3f}s".format(t1 / 10))
    print("Tempo para cálculo da Arvore de Steiner: {:.3f}s".format(t2 / 10))
    print("Tamanho da Arvore de Steiner:", l)


def load_graph(path):
    f = open(path, "r")
    g = dict()
    v = int(f.readline())
    for vertex in range(v):
        edges = list(f.readline().replace("\n", "").split())
        g[str(vertex)] = edges
    return g


if __name__ == "__main__":
    if input("Deseja gerar um grafo aleatóriamente? s ou n\n ->") == "s":
        size = int(input("Digite a quantidade de vértices do grafo G\n ->"))
        percent = float(input("Digite a porcentagem de conexão do grafo G\n ->")) / 100
        gen_timer = time.time()
        g = create_random_graph(size, percent)
        gen_timer = time.time() - gen_timer
    else:
        g = connect_components(
            get_connected_components(load_graph(input("Digite o nome do arquivo\n ->")))
        )
        gen_timer = 0
    terminals = pick_random_terminals(
        g, int(input("Digite a quantidade de nós terminais\n ->"))
    )
    render_initial_graph(g, terminals)
    steiner_timer = time.time()
    a = input("Grafo inicial gerado")
    tree_edges, l = get_steiner_tree(g, terminals)
    steiner_timer = time.time() - steiner_timer
    render_steiner_solution(g, terminals, tree_edges)
    statistics(gen_timer, steiner_timer, l)
