from graphviz import Graph

 ################################################
 #   Autor: Vinicius Gasparini
 #   Nome: Renderizador de MST
 ################################################

def save_graph(dot, name):
    dot.format = 'pdf'
    dot.render(name)

def render_graph(g_list,size,mst_edges,mst_nodes):
    dot = Graph()
    for idx in range(size):
        if idx in mst_nodes:
            dot.node(str(idx),style='filled', color='lightgrey')
        else:
            dot.node(str(idx))
    for u,v,w in g_list:
        if [u,v,w] in mst_edges:
            dot.edge(str(u),str(v),str(w),color='red')
        else:
            dot.edge(str(u),str(v),str(w))
    save_graph(dot,'mst_graph')

def load_graph(path):
    f = open(path,'r')
    g_list = []
    mst_edges,mst_nodes = [],set()
    size,edges,mst_size = map(int,f.readline().split())
    for vertex in range(edges):
        edges = list(map(int,list(f.readline().replace('\n','').split())))
        g_list.append(edges)
    for vertex in range(mst_size):
        edges = list(map(int,list(f.readline().replace('\n','').split())))
        mst_edges.append(edges)
        mst_nodes.add(edges[0])
        mst_nodes.add(edges[1])
    return g_list,size,mst_edges,mst_nodes

if __name__ == '__main__':
    g_list,size,mst_edges,mst_nodes = load_graph(input('Input filename-> '))
    render_graph(g_list,size,mst_edges,mst_nodes)