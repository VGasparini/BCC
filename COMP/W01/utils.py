from random import randrange as r
import os

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

def print_pilha(s):
    print(str(s).replace(',','').replace("'",'')[2:-2])