from graphviz import Digraph
from random import randrange as r
import os
from glob import glob

def read_quintuple_from_data(file):
    f = open(file, "r")
    name = f.readline().replace("\n", "")
    alphabet = set([symbol for symbol in f.readline().replace("\n", "").split()])
    states = set([state for state in f.readline().replace("\n", "").split()])
    number_transitions = int(f.readline())
    delta_function = dict()
    for transition in range(number_transitions):
        r_input = f.readline()
        r_input = (r_input.replace(":", "->").replace("\n", "")).split("->")
        delta_function[(r_input[0], r_input[2])] = r_input[1]
    start_state = f.readline().replace("\n", "")
    final_states = set([state for state in f.readline().split()])
    f.close()

    return name, alphabet, states, delta_function, start_state, final_states


def read_7_tuple_from_data(file):
    f = open(file, "r")
    name = f.readline().replace("\n", "")
    alphabet = set([symbol for symbol in f.readline().replace("\n", "").split()])
    states = set([state for state in f.readline().replace("\n", "").split()])
    delta_function = dict()
    number_transitions = int(f.readline())
    for transition in range(number_transitions):
        r_input = f.readline()
        r_input = (r_input.replace(":", "->").replace("\n", "")).split("->")
        delta_function[(r_input[0], r_input[2])] = r_input[1]
    start_state = f.readline().replace("\n", "")
    final_states = set([state for state in f.readline().split()])
    output_alphabet = set([symbol for symbol in f.readline().replace("\n", "").split()])
    number_output = int(f.readline())
    output_function = dict()
    for transition in range(number_output):
        r_input = f.readline()
        r_input = (r_input.replace("\n", "")).split("->")
        output_function[r_input[0]] = r_input[1]
    confiabilitty = int(f.readline())
    capacity = int(f.readline())
    f.close()
    return (
        name,
        alphabet,
        states,
        delta_function,
        start_state,
        final_states,
        output_alphabet,
        output_function,
        confiabilitty,
        capacity,
    )


def read_regex(file):
    f = open(file, "r")
    regex = f.readline().replace("\n", "")
    f.close()
    return regex


def nickname(file):
    f = open(file, "r")
    n = int(f.readline())
    nicks = dict()
    for line in range(n):
        r_input = f.readline()
        r_input = (r_input.replace("\n", "")).split(":")
        nicks[r_input[0]] = r_input[1]
    return nicks


def export_graph(file, automaton):
    f = Digraph(file, filename=file)
    f.attr(rankdir="LR", size="8,5")

    f.attr("node", shape="doublecircle")
    for node in automaton.final_states:
        f.node(node)

    f.attr("node", shape="circle")
    for transition, letter in automaton.delta_function:
        f.edge(transition, automaton.delta_function[(transition, letter)], label=letter)
        f.node(automaton.current_state, color="red")

    f.render(directory="saida")

def export_error(file, automaton, error):
    f = Digraph(file, filename=file)
    f.attr(rankdir="LR", size="8,5")

    f.attr("node", shape="doublecircle")
    for node in automaton.final_states:
        f.node(node)

    f.attr("node", shape="circle")
    for transition, letter in automaton.delta_function:
        f.edge(transition, automaton.delta_function[(transition, letter)], label=letter)
        f.node(error, color="red")

    f.render(directory="saida")


def header(text):
    print()
    print("-" * 15)
    print(text.upper())
    print("-" * 15)
    print()

def generate_demand():
    if input("Deseja gerar uma demanda aleatória?\n(s ou n) ->") == 's':
        op = input("Deseja uma demanda válida ou inválida?\n(v ou i) ->")
        n = int(input("Digite o tamanho da demanda a ser gerada\n ->"))

        g_cor = ['Z','B', 'P', 'V']
        g_tipo = ['!', '#']

        b_cor = ['L', 'B', 'P', 'V']
        b_tipo = ['@', '&']

        j_cor = ['B', 'P', 'V', 'Z']
        j_tipo = ['@', '#']

        m_cor = ['B', 'P', 'V', 'R']
        m_tipo = ['$', '#']

        n_cor = ['B', 'P', 'V', 'L']
        n_tipo = ['@', '#']

        u_cor = ['B', 'P', 'V', 'R']
        u_tipo = ['@', '#']

        w_cor = ['B', 'P', 'V', 'A']
        w_tipo = ['!', '#']

        z_cor = ['B', 'P', 'V', 'A']
        z_tipo = ['$', '#']

        modelos = ['b','g','j','m','n','u','w','z']
        cores = [b_cor,g_cor,j_cor,m_cor,n_cor,u_cor,w_cor,z_cor]
        tipos = [b_tipo,g_tipo,j_tipo,m_tipo,n_tipo,u_tipo,w_tipo,z_tipo]

        word = ''
        for i in range(n):
            index = r(8)
            w = str(modelos[index])+str(cores[index][r(4)])+str(tipos[index][r(2)])+';'
            word += w
        if op == 'i':
            word += '1'
        print("Demanda gerada = ",word)
        print("Enviando para a produção\n")
    else:
        word = input("Digite a demanda\n ->")
    return word

def clean():
    print()
    if input("Deseja conservar as saidas geradas?\n(s ou n) ->") == 'n':
        files = glob('./saida/*')
        for f in files:
            os.remove(f)




