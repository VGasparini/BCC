import galapagos as gp
from galapagos.utils import binaryToInt
from numpy import ndarray
import galapagos.selector as sl
import galapagos.operators.crossover as cr
import galapagos.operators.mutation as mt
import math
from galapagos.log_handler import plot_runs, convergence_chart
from numba import njit
import maze_board as bd
import numpy as np
from functools import partial


@njit
def fitness(maze: np.ndarray, individual: np.ndarray) -> (np.ndarray, float):
    max_fitness = math.ceil(
        math.sqrt(((0 - len(maze)) ** 2) + ((0 - len(maze[0])) ** 2)) + 100
    )
    end = bd.get_end(maze)
    init = bd.get_init(maze)
    position, blocked, walked_open, returned = bd.walk(individual, maze)
    distance_end = math.ceil(
        math.sqrt(((position[0] - end[0]) ** 2) + ((position[1] - end[1]) ** 2))
    )

    distance_init = math.ceil(
        math.sqrt(((position[0] - init[0]) ** 2) + ((position[1] - init[1]) ** 2))
    )
    # print(
    #     1000 - distance_init * (blocked + returned - walked_open),
    #     blocked,
    #     position[0],
    #     position[1],
    # )
    return (individual, max_fitness - distance_end - blocked - returned)


if __name__ == "__main__":
    maze = bd.read()
    result = gp.run(
        partial(fitness, maze),
        mutation_function=mt.random_replacement,
        crossover_function=cr.uniform,
        select_function=sl.stochastic_tournament,
        config_file="maze.cfg",
    )

    # convergence_chart(result)
    maze_result = bd.simulate(result["champion"][0], maze)
    print(result["champion"][0])
    bd.fig(maze_result, "./out/maze_result.png")
