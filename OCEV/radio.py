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
    rl, rs = normalization(chromosome)

    out = f"Luxury radio: {rl}\n"
    out += f"Standard radio: {rs}\n"
    out += f"Profit: {(40*rl+30*rs)}"

    return out


def normalization(ind: ndarray):
    xrl = binaryToInt(ind[: len(ind) // 2])
    xrs = binaryToInt(ind[len(ind) // 2 :])
    # rs [0-24] -> 5 bits
    # rl [0-16] -> 5 bits
    rl = math.floor(0 + (16 / 31) * xrl)
    rs = math.floor(0 + (24 / 31) * xrs)

    return rl, rs


def fitness(ind: ndarray):
    rl, rs = normalization(ind)

    r = -1
    FOn = (30 * rs + 40 * rl) / 1360
    Hn = max(0, (rs + 2 * rl - 40)) / 16
    fit = FOn + r * Hn

    return ind, fit


if __name__ == "__main__":

    result = gp.run(
        fitness,
        mutation_function=mt.bit_flip,
        crossover_function=cr.two_points,
        select_function=sl.fitness_proportionate_selection,
        config_file="radio.cfg",
        phenotype=show,
    )

    convergence_chart(result, False)
    plot_runs(result)


"""
conjunto: radio standart, luxo
dominio:
rs [0-24] -> 5 bits
rl [0-16] -> 5 bits

cromosomo: 10bits

rs + 2rl  =< 40

fitness: normalizacoao da FO das restricoes (H) e definicao do coeficiente de penalidade(r)

fit= FOn + rHn
r = -1

FOn = (30RS + 40RL)/1360

Hn = max(0, RS + 2RL - 40)/16
"""
