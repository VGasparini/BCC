Xi = [i/10 for i in range(-50,25,5)]
Yi = [0.11,-1.04,-5,4.97,0.74,-2.15,3.3,-0.92,-4.79,1.99,1.71,3.68,2.81,-3.71,-1.1]

grau = len(Yi)
Ai = [1 for i in range(grau)]

for i in range(grau):
    t = 1
    for j in range(grau):
        if i != j:
            t *= (Xi[i]-Xi[j])
    Ai[i] = Yi[i] / t    
for i in range(grau):
    print()
    print("a_{{{}}}={:.15f}".format(i, Ai[i]))