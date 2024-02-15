from numba import njit
import numpy as np
from numpy import ndarray
import matplotlib.pyplot as plt
import matplotlib
from matplotlib import colors as c
from matplotlib.pyplot import figure


def read(path: str = "maze.txt") -> ndarray:
    out = []
    with open(path, "r") as file:
        for line in file:
            out.append(np.array([int(y) for y in line.split()]))

    return np.array(out)


def fig(maze: ndarray, out_path: str = "out_maze.png") -> None:
    cMap = c.ListedColormap(["k", "w", "c", "y", "r"])
    figure(num=None, figsize=(8, 8), dpi=80)
    plt.pcolormesh(maze, cmap=cMap)
    plt.axes().set_aspect("equal")
    plt.xticks([])
    plt.yticks([])
    plt.axes().invert_yaxis()
    plt.savefig(out_path)


@njit
def walk(individual: ndarray, maze: ndarray) -> (int, int):

    init = get_init(maze)
    maze_copy = maze.copy()
    robot = (init[0], init[1])
    blocked = 0
    walked_open = 0
    returned = 0

    for command in individual:
        if command != 0:
            position = step(command, robot)
            if position and maze_copy[position[0]][position[1]] != 0:
                if maze_copy[position[0]][position[1]] in [2, 3]:
                    returned += 1
                else:
                    walked_open += 1
                robot = position
                maze_copy[position[0]][position[1]] = 3

            else:
                blocked += 1
    return (robot, blocked, walked_open, returned)


def simulate(individual: ndarray, maze: ndarray) -> ndarray:
    init = get_init(maze)
    robot = (init[0], init[1])

    for command in individual:
        if command != 0:
            position = step(command, robot)
            if position and maze[position[0]][position[1]] != 0:
                robot = position
                if simulate:
                    maze[position[0]][position[1]] = 3

    return maze


@njit
def step(command: int, pos: (int, int)) -> (int, int):
    if command == 1:
        out = (pos[0], pos[1] - 1)
    if command == 2:
        out = (pos[0] + 1, pos[1])
    if command == 3:
        out = (pos[0], pos[1] + 1)
    if command == 4:
        out = (pos[0] - 1, pos[1])
    return out


@njit
def get_init(maze: ndarray) -> ndarray:
    init_cordinates = np.where(maze == 2)
    init = np.dstack((init_cordinates[0], init_cordinates[1]))[0]
    if len(init) == 0:
        raise Exception("The maze doest have a init!")
    if len(init) > 1:
        raise Exception("The maze has 2 or more inits!")

    return init[0]


@njit
def get_end(maze: ndarray) -> ndarray:
    end_cordinates = np.where(maze == 4)
    end = np.dstack((end_cordinates[0], end_cordinates[1]))[0]
    if len(end) == 0:
        raise Exception("The maze doest have a end!")
    if len(end) > 1:
        raise Exception("The maze has 2 or more ends!")

    return end[0]