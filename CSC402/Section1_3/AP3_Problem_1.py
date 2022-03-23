def heaviside(x):
  if x >= 0:
    return 1
  else:
    return 0

def sigma(x):
  return 1/(1 + 2.71828**(-x))

print('================================')
print('========== Perceptrons =========')
data = [(0,0,0),(0,0,1),(0,1,0),(0,1,1),(1,0,0),(1,0,1),(1,1,0),(1,1,1)]
for d in data:
  a0 = [d[i] for i in range(len(d))]
  print('================================')
  print('d =',d)
  #First Layer Values
  W1 = [[80,60,70],[50,30,0],[90,40,40]]
  b1 = [-130,-30,-70]

  a1 = []
  for j in range(len(W1)):
    a1.append(sigma(sum(W1[i][j]*a0[i] for i in range(len(W1))) + b1[j]))
  #Use heaviside for Perceptrons
  #Use sigma for Sigmoid Neurons

  print('1st Layer Activation')
  print('a_0^1 =',a1[0])
  print('a_1^1 =',a1[1])
  print('a_2^1 =',a1[2])

  #Second Layer Values
  W2 = [[10,30],[30,70],[50,20]]
  b2 = [-40,-110]
  a2 = []
  for j in range(len(W2[0])):
    a2.append(sigma(sum(W2[i][j]*a1[i] for i in range(len(W2))) + b2[j]))
  #Use heaviside for Perceptrons
  #Use sigma for Sigmoid Neurons

  print('2nd Layer (Final) Activation')
  print('a_0^2 =', a2[0])
  print('a_1^2 =', a2[1])
