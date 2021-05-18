from __future__ import division
import numpy as np
from numpy import linalg


def jacobi(A, b, x0, tol, N):
    # preliminares
    A, b, x0 = A.astype("double"), b.astype("double"), x0.astype("double")

    n = np.shape(A)[0]
    x = np.zeros(n)
    it = 0
    # iteracoes
    while it < N:
        it = it + 1
        # iteracao de Jacobi
        for i in np.arange(n):
            x[i] = b[i]
            for j in np.concatenate((np.arange(0, i), np.arange(i + 1, n))):
                x[i] -= A[i, j] * x0[j]
            x[i] /= A[i, i]
        # tolerancia
        if np.linalg.norm(x - x0, np.inf) < tol:
            return x
        # prepara nova iteracao
        x0 = np.copy(x)
    raise NameError("num. max. de iteracoes excedido.")


def gauss_seidel(A, b, x0, tol, N):
    # preliminares
    A, b, x0 = A.astype("double"), b.astype("double"), x0.astype("double")

    n = np.shape(A)[0]
    x = np.copy(x0)
    it = 0
    # iteracoes
    while it < N:
        it = +1
        # iteracao de Jacobi
        for i in np.arange(n):
            x[i] = b[i]
            for j in np.concatenate((np.arange(0, i), np.arange(i + 1, n))):
                x[i] -= A[i, j] * x[j]
            x[i] /= A[i, i]
        # tolerancia
        if np.linalg.norm(x - x0, np.inf) < tol:
            return x
        # prepara nova iteracao
        x0 = np.copy(x)
    raise NameError("num. max. de iteracoes excedido.")


A = np.matrix(
    [
        [1, -1, 0, 0, 0],
        [-1, 2, -1, 0, 0],
        [0, -1, (2 + 10 ** -3), -1, 0],
        [0, 0, -1, 2, -1],
        [0, 0, 0, 1, 2],
    ]
)
b = np.matrix([[1], [1], [1], [1], [1]])
x0 = np.matrix([[0], [0], [0], [0], [0]])

print("Metodo Eliminacao de Gauss")
A_inversa = np.linalg.inv(A)
x = np.dot(A_inversa, b)
for i in range(5):
    print("x{} = {}".format(i + 1, x[i, 0]))
print

print("Metodo Jacobi")
x = jacobi(A, b, x0, 10 ** -2, 100)  # utilizando 100 iteracoes
for i in range(5):
    print("x{} = {}".format(i + 1, x[i]))
print

print("Metodo Gauss-Seidel")
x = gauss_seidel(A, b, x0, 10 ** -2, 100)  # utilizando 100 iteracoes
for i in range(5):
    print("x{} = {}".format(i + 1, x[i, 0]))
