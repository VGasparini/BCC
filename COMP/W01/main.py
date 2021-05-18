from class_DFA import DFA
from utils import *


def simplifica(pilha, op):
    x = pilha.pop()
    y = pilha.pop()
    pilha.append((y, op, x))


const = DFA(*read_quintuple_from_data("const"))
soma = DFA(*read_quintuple_from_data("soma"))
subtracao = DFA(*read_quintuple_from_data("subtracao"))
multiplicacao = DFA(*read_quintuple_from_data("multiplicacao"))
divisao = DFA(*read_quintuple_from_data("divisao"))

data = [i for i in input("Digite a expressão: ").split()]

exp = {}

pilha = []

for word in data:
    if const.run_with_word(word):
        pilha.append(word)
        # if len(pilha) > 2:
        #     print('não reconhecido')
        #     exit()
    elif soma.run_with_word(word):
        if len(pilha) > 0:
            simplifica(pilha, word)
    elif subtracao.run_with_word(word):
        if len(pilha) > 0:
            simplifica(pilha, word)
    elif multiplicacao.run_with_word(word):
        if len(pilha) > 0:
            simplifica(pilha, word)
    elif divisao.run_with_word(word):
        if len(pilha) > 0:
            simplifica(pilha, word)
    else:
        print("não reconhecido")
        exit()
if len(pilha) == 1:
    print_pilha(pilha)
else:
    print("expressão inválida")
