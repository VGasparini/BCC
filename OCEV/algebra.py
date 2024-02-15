import galapagos as gp
from galapagos.utils import binaryToInt
from numpy import ndarray
import galapagos.selector as sl
import galapagos.operators.crossover as cr
import galapagos.operators.mutation as mt
import math
from galapagos.log_handler import plot_runs, convergence_chart

# Problema do Radio
# 40 funcionarios
# S = Radio Standard: 1/dia -> R$30 (Restricao: max 24 funcionarios)
# L = Radio Luxo: 2/dia -> R$40 (Restricao: max 32 funcionarios)
# f(x) =


def show(chromosome: ndarray):
    i = normalization(chromosome)

    out = f"x: {i}\n"
    out += f"f(x): {math.cos(20*i) - abs(i/2) + (i**3)/4}"

    return out


def normalization(ind: ndarray):
    d=0
    for n,i in enumerate(ind):
        d += i*2**n
    return -2 + (4/(2**16-1))*d


def fitness(ind: ndarray):
    i = normalization(ind)
    fit = math.cos(20*i) - abs(i/2) + (i**3)/4
    fit = fit-2
    fit = -fit/6
    return ind, fit


if __name__ == "__main__":

    result = gp.run(
        fitness,
        mutation_function=mt.bit_flip,
        crossover_function=cr.two_points,
        select_function=sl.fitness_proportionate_selection,
        config_file="algebra.cfg",
        phenotype=show,
    )

    convergence_chart(result, False)
    plot_runs(result)


"""
U = {-2, 2}
P = 10-4

2^L-1 < (2 - (-2)) / 10^-4 < 2^L => 2^L-1 < 4/10^-4 < 2^L => 2^L-1 < 40000 < 2^L => L = 16

L = 16
"""
