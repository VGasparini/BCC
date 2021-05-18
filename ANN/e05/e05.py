from pprint import pprint
from numpy import array, diag, diagflat
from numpy import dot, linalg, triu, tril


def gauss_seidel(A, b, N, x):
    D = diagflat(diag(A))
    L = tril(A, -1)
    U = triu(-A, 1)
    D_L = D + L
    D_L_ = linalg.inv(D_L)

    for i in range(N):
        x = dot(D_L_, (dot(U, x) + b))
        print("X(%d) = " % (i + 1), end="")
        print(x)
    return x


A = array(
    [
        [10.7, -2.3, 2.4, -2.2, -0.9],
        [-0.7, 12.6, 2.7, -2.0, 1.8],
        [1.1, 1.0, 11.1, -2.2, 2.0],
        [-2.5, -1.4, 0.3, 9.5, 2.4],
        [-2.1, 1.2, -0.3, -1.5, 7.5],
    ]
)

b = array([3.8, 1.6, -4.4, 1.9, 0.8])
chute = array([1.4, -4.6, 2.8, 1.7, -2.5])

sol = gauss_seidel(A, b, N=9, x=chute)

print("A:", end=" ")
pprint(A)

print("b:", end=" ")
print(b)

print("x:", end=" ")
print(sol)
