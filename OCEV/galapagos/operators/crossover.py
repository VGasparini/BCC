import numpy as np
from numba import njit


def one_point(
    parent_1: np.ndarray, parent_2: np.ndarray, index: int = -1
) -> np.ndarray:
    if index == -1:
        index = int(np.random.uniform(low=1, high=len(parent_1) - 1))
    return np.array(
        [
            np.hstack([parent_1[:index], parent_2[index:]]),
            np.hstack([parent_2[:index], parent_1[index:]]),
        ]
    )


def two_points(parent_1: np.ndarray, parent_2: np.ndarray) -> np.ndarray:
    crom_size = len(parent_1) - 1

    index_1 = int(np.random.uniform(low=1, high=crom_size - 2))
    index_2 = int(np.random.uniform(low=index_1, high=crom_size))

    child_1, child_2 = one_point(parent_1, parent_2, index_1)

    return one_point(child_1, child_2, index_2)


def uniform(parent_1: np.ndarray, parent_2: np.ndarray) -> np.ndarray:
    choose = np.random.rand(len(parent_1))

    for i in range(len(choose)):
        if choose[i] < 0.5:
            temp = parent_1[i]
            parent_1[i] = parent_2[i]
            parent_2[i] = temp
    return np.array([parent_1, parent_2])


def pmx(parent_1: np.ndarray, parent_2: np.ndarray) -> np.ndarray:
    size = min(len(parent_1), len(parent_2))
    p1, p2 = [0] * size, [0] * size

    for i in range(size):
        p1[parent_1[i] - 1] = i
        p2[parent_2[i] - 1] = i

    point1 = np.random.randint(0, size)
    point2 = np.random.randint(0, size - 1)
    if point2 >= point1:
        point2 += 1
    else:
        point1, point2 = point2, point1

    for i in range(point1, point2):
        temp1 = parent_1[i]
        temp2 = parent_2[i]

        parent_1[i], parent_1[p1[temp2 - 1]] = temp2, temp1
        parent_2[i], parent_2[p2[temp1 - 1]] = temp1, temp2

        p1[temp1 - 1], p1[temp2 - 1] = p1[temp2 - 1], p1[temp1 - 1]
        p2[temp1 - 1], p2[temp2 - 1] = p2[temp2 - 1], p2[temp1 - 1]

    return np.array([parent_1, parent_2])
