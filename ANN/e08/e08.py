import numpy as np
from numpy import linalg
from pprint import pprint

Xi = np.array([i/10 for i in range(-50, 55, 5)])
Yi = np.array([-1.82, -1.44, -0.99, -4.09, -4.49,
               -0.28, -3.37, 3.23, -2.93, 0.68,
               -2.12, -3.54, 0.74, -0.21, -0.91,
               -2.3, 0.19, 0.52, -1.76, 0.98, 2.07])

grau = len(Xi)
ans = [[0 for j in range(grau)] for i in range(grau)]
for i in range(grau):
    ans[i][0] = Yi[i]

for i in range(1, grau):
    for j in range(1, i+1):
        ans[i][j] = (ans[i][j-1] - ans[i-1][j-1]) / (Xi[i] - Xi[i-j])
for i in range(grau):
    print("a_{{{}}}={:.15f}".format(i, ans[i][i]))
