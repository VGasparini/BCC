import galapagos as gp
from numpy import ndarray
import numpy as np
import galapagos.operators.crossover as cr
import galapagos.operators.mutation as mt
import galapagos.selector as sl
from galapagos.log_handler import plot_runs, convergence_chart
from numba import njit


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

    return out

@njit
def fitness(individual: ndarray):
    dim = len(individual)
    max_fit = dim * (dim - 1)
    fit = max_fit
    for i in range(len(individual) - 1):
        for j in range(i + 1, len(individual)):
            fit -= 2 * (abs(individual[i] - individual[j]) == abs(i - j))
    return individual, fit / max_fit


if __name__ == "__main__":
    result = gp.run(
        fitness,
        mutation_function=mt.swap,
        crossover_function=cr.pmx,
        select_function=sl.stochastic_tournament,
        config_file="n_queens.cfg",
        phenotype=show_table,
    )

    convergence_chart(result, False)
    plot_runs(result)
