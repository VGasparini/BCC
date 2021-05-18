from pprint import pprint
from numpy import array, dot, linalg


def g(x1, x2):
    g_1 = x1 * x1 - 3 * x2 * x2 + 5
    g_2 = x1 * x1 + 2 * x2 * x2 - 5
    return array([g_1, g_2])


def g_(x1, x2):
    g_11 = 2 * x1
    g_12 = -6 * x2
    g_21 = 2 * x1
    g_22 = 4 * x2
    return array([[g_11, g_12], [g_21, g_22]])


def newton(N, x):
    for i in range(N):
        x1, x2 = x
        x = x - dot(linalg.inv(g_(x1, x2)), g(x1, x2))
        print("X(%d) = [%.8f,%.8f]" % (i + 1, x1, x2))
    return x1, x2


chute = array([1.23, 1.3])

x1, x2 = newton(N=4, x=chute)

print("x:[%.8f,%.8f]" % (x1, x2))
