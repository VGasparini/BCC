from pprint import pprint
import numpy as np

Xi = [i/10 for i in range(0, 35, 5)]
Yi = [1.94, 1.69, 2.17, 2.55, 1.25, 1.69, 1.28]
grau = len(Xi)

Hi = []
for i in range(grau-1):
  Hi.append(Xi[i + 1] - Xi[i])

diag_Hi = [[0 for i in range(grau)] for j in range(grau)]
diag_Hi[0][0] = 1
diag_Hi[-1][-1] = 1


for i in range(1, grau - 1):
  for j in range(grau):
    if j == (i - 1):
      diag_Hi[i][j] = Hi[i]
    elif j == i:
      diag_Hi[i][j] = 2 * (Hi[j-1] + Hi[(j)])
    elif j == (i + 1):
      diag_Hi[i][j] = Hi[i]


Ai = [0 for i in range(grau)]

for i in range(1, grau - 1):
  Ai[i] = (3 / Hi[i]) * (Yi[i + 1] - Yi[i]) - (3 / Hi[i - 1]) * (Yi[i] - Yi[i - 1])

Ci = np.linalg.solve(diag_Hi, Ai)

Di = [0 for i in range(grau)]
for i in range(len(Ci) - 1):
  Di[i] = (Ci[i + 1] - Ci[i]) / (3 * Hi[i])

Bi = [0 for i in range(grau)]
for i in range(len(Ci) - 1):
  Bi[i] = ((Yi[i + 1] - Yi[i]) / Hi[i]) - (Hi[i] / 3 * (Ci[i + 1] + 2 * Ci[i]))

for i in range(0, len(Yi)-1):
  print('a_{} = {:.15f}'.format(i, Yi[i]))
  print()
for i in range(0, len(Bi)-1):
  print('b_{} = {:.15f}'.format(i, Bi[i]))
  print()
for i in range(0, len(Ci)-1):
  print('c_{} = {:.15f}'.format(i, Ci[i]))
  print()
for i in range(0, len(Di)-1):
  print('d_{} = {:.15f}'.format(i, Di[i]))
  print()