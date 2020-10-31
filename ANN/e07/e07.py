from __future__ import division
import numpy as np
from numpy import linalg
from numpy.polynomial import polynomial as poly
import matplotlib.pyplot as plt

Xi = np.array([i/10 for i in range(-25, 50, 5)])
Yi = np.array([3.35, 2.6, 3.06, 4.38, 0.49, 0.15, 4.41,
               2.75, 4.3, 3.64, 0.01, 3.21, 4.82, 4.27, 1.85])
grau = len(Xi)
S = np.array([Xi**i for i in range(grau-1, -1, -1)]).transpose()
ans = np.linalg.inv(S).dot(Yi)[::-1]
for i in range(len(ans)):
    print("a_{{{}}}={:.7f}".format(i, ans[i]))

xx = np.linspace(min(Xi)-.05, max(Xi)+.05)
plt.plot(Xi, Yi, 'ro', xx, np.polyval(ans[::-1], xx), 'b')
plt.grid()
plt.show()
