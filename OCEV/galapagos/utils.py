from numpy import ndarray


def binaryToInt(individual: ndarray) -> int:
    out = 0
    for bit in individual:
        out = (out << 1) | bit

    return out
