from functools import partial
import numpy as np
import math
from os import environ


def binary_random(size: int) -> np.ndarray:
    environ["LOW"] = "0"
    environ["HIGH"] = "1"
    return np.random.randint(0, 2, size, dtype="uint8")


def integer_permutation(size: int, low: int, high: int) -> np.ndarray:
    return np.random.permutation(range(math.floor(low), math.floor(high + 1)))


def integer_random(size: int, low: int, high: int) -> np.ndarray:
    return np.random.randint(math.floor(low), math.floor(high + 1), size)


def real_random(size: int, low: int, high: int) -> np.ndarray:
    return np.random.uniform(low, high, size)


def gen(population_size, populationgen: callable, population=[]) -> np.ndarray:
    num = population_size - len(population)
    return np.array(population + [populationgen() for _ in range(num)])


def get() -> callable:
    chromosome_size, low, high, key = (
        int(environ["DIM"]),
        int(environ["LOW"]),
        int(environ["HIGH"]),
        environ["COD"],
    )

    generator = {
        "BIN": partial(binary_random, chromosome_size),
        "INT_PERM": partial(integer_permutation, chromosome_size, low, high),
        "INT": partial(integer_random, chromosome_size, low, high),
        "REAL": partial(real_random, chromosome_size, low, high),
    }

    if key not in generator:
        raise Exception(
            "Population",
            (
                f'key "{key}"" does not exist use one of {[i for i in generator]} instead'
            ),
        )

    return partial(gen, int(environ["POP"]), generator[key])
