from pprint import pprint
from numpy import array, diag, diagflat, dot, linalg


def jacobi(A, b, N, x):
    D_ = diagflat(diag(A))
    L_U = A - D_
    D_ = linalg.inv(D_)

    for i in range(N):
        x = dot(dot(-D_, L_U), x) + dot(D_, b)
        print("X(%d) = " % (i + 1), end="")
        print(x)
    return x


A = array([[3, -1, 1], [1, 4, 1], [1, 1, 5]])

b = array([3, 8, -2])
chute = array([0, -1, 2])

sol = jacobi(A, b, N=9, x=chute)

print("A:", end=" ")
pprint(A)

print("b:", end=" ")
print(b)

print("x:", end=" ")
print(sol)
