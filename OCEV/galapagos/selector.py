import random
import numpy as np


def fitness_proportionate_selection(population: np.ndarray) -> np.ndarray:
    selected = []
    removed_fitness = None
    sum_fit = float(sum([c[1] for c in population]))

    for _ in range(len(population)):
        lucky_number = random.random()
        prev_probability = 0.0

        if removed_fitness is not None:
            population[index][1] = removed_fitness
            sum_fit += removed_fitness
            removed_fitness = None

        for i, c in enumerate(population):
            if (prev_probability + (c[1] / sum_fit)) >= lucky_number:
                selected.append(np.array(c[0]))
                sum_fit -= c[1]
                removed_fitness = c[1]
                index = i
                c[1] = 0
                break
            prev_probability += c[1] / sum_fit

    return np.array(selected)


def stochastic_tournament(population: np.ndarray, k: int = 2, kp: int = 1) -> np.array:
    def fight(subpop):
        lucky_number = random.random()
        if kp >= lucky_number:
            return subpop[1][0]
        return subpop[0][0]

    weights = [1 for i in population]
    return np.array(
        [
            fight(
                sorted(
                    random.choices(population, k=k, weights=weights), key=lambda x: x[1]
                )[0 :: k - 1]
            )
            for i in population
        ]
    )
