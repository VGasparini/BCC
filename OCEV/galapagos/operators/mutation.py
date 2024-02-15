import numpy as np

from os import environ


def bit_flip(chromosome: np.ndarray, **kwargs) -> np.ndarray:
    choose = np.random.rand(len(chromosome))

    for i in range(len(choose)):
        if choose[i] < 0.5:
            chromosome[i] = 1 if chromosome[i] == 0 else 0

    return chromosome


def swap(chromosome: np.ndarray, **kwargs):
    point_1 = np.random.randint(len(chromosome))
    point_2 = np.random.randint(len(chromosome))
    while point_1 == point_2:
        point_2 = np.random.randint(len(chromosome))
    chromosome[point_1], chromosome[point_2] = chromosome[point_2], chromosome[point_1]

    return chromosome


def random_replacement(chromosome: np.ndarray, **kwargs) -> np.ndarray:
    point = np.random.randint(len(chromosome))
    chromosome[point] = np.random.randint(
        low=int(environ["LOW"]), high=int(environ["HIGH"])
    )
    return chromosome


def __delta(t, y, b=5):
    return y * (1 - np.random.rand() ** (((1 - t) / int(environ["GEN"])) ** b))


def michalewicz(chromosome: np.ndarray, iteration: int, **kwargs) -> np.ndarray:
    for c in chromosome:
        c += __delta(
            iteration,
            abs(
                c
                - (
                    int(environ["HIGH"])
                    if np.random.randint(0, 2)
                    else int(environ["LOW"])
                )
            ),
        )
