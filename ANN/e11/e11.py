N       = [[1.0352447188],
           [2.5855945787],
           [3.2388323353],
           [3.4710646839],
           [3.5579700434],
           [3.5936432168],
           [3.6094908928]]

grau    = 7
b       = 1

for i in range (grau - 1):
  for j in range (grau - i - 1): 
    N[j].append( ( ( 2**(i*b + b) * N[j + 1][i] ) - N[j][i])
                    / (2**(i*b + b) - 1) )
print('N_%d(1) = %.10f' % (grau,N[0][-1]))
