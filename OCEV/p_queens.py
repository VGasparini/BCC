import galapagos as gp
from numpy import ndarray
import numpy as np
import galapagos.operators.crossover as cr
import galapagos.operators.mutation as mt
import galapagos.selector as sl
from galapagos.log_handler import plot_runs, convergence_chart, show_population
from galapagos.config import parse
from numba import njit
from os import environ
import math

def show_table(chromosome: np.ndarray) -> str:
    size = len(chromosome)
    board = np.full((size, size), ".")

    for index, item in enumerate(chromosome):
        board[index][item - 1] = "x"

    out = ""
    for row in board:
        out += "|"
        for tile in row:
            out += tile
        out += " |\n"

    col, profit = 0, 0
    for i in range(len(chromosome)):
        profit += profit_array[(size * i) + (chromosome[i] - 1)]
        for j in range(i + 1, len(chromosome)):
            col += 2 * (abs(chromosome[i] - chromosome[j]) == abs(i - j))

    out += f"\ncollisions: {col}\n"
    out += "profit: %f/%f\n" % (profit, max_fit_profit)

    return out


@njit
def fitness(individual: ndarray):
    dim = len(individual)
    
    max_colision = dim * (dim - 1) // 2
    colision = max_colision

    profit: float = 0
    for i in range(len(individual)):
        profit += profit_array[(dim * i) + (individual[i] - 1)]
        for j in range(i + 1, len(individual)):
            colision -= 2 * (abs(individual[i] - individual[j]) != abs(i - j))

    return individual, profit / max_fit_profit - colision / max_colision


if __name__ == "__main__":
    parse("p_queens.cfg")
    array_length = int(environ.get("DIM"))

    profit_array = np.array(list(map(float, range(1, array_length ** 2 + 1))))
    op, po = math.sqrt, math.log10
    for i in range(len(profit_array)):
        profit_array[i] = op(profit_array[i])
        if (i + 1) % array_length == 0:
            op, po = po, op
            continue

    max_fit_profit = sum(profit_array[array_length * array_length - 2 * array_length :])
    # print(show_table(np.array([1,8,15,11,7,3,16,9,12,14,5,2,6,13,10,4])))
    result = gp.run(
        fitness,
        mutation_function=mt.swap,
        crossover_function=cr.pmx,
        select_function=sl.stochastic_tournament,
        config_file="p_queens.cfg",
        phenotype=show_table,
        pool_size=4,
    )

    convergence_chart(result, False)
    # plot_runs(result,False)
