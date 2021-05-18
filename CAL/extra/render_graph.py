from graphviz import Graph

################################################
#   Autor: Vinicius Gasparini
#   Nome: Renderizador de grafos
################################################


def save_graph(dot, name):
    dot.format = "pdf"
    dot.render(name)


def render_graph(g_list, size):
    dot = Graph()
    for idx in range(size):
        dot.node(str(idx))
    for u, v, w in g_list:
        dot.edge(str(u), str(v), str(w))
    save_graph(dot, "initial_graph")


def load_graph(path):
    f = open(path, "r")
    g_list = []
    size, edges = map(int, f.readline().split())
    for vertex in range(edges):
        edges = list(map(int, list(f.readline().replace("\n", "").split())))
        g_list.append(edges)
    return g_list, size


if __name__ == "__main__":
    g_list, size = load_graph(input("Input filename-> "))
    render_graph(g_list, size)
