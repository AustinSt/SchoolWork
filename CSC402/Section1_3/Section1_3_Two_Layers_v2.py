def heaviside(x):
  if x >= 0:
    return 1
  else:
    return 0

print('=========================')
print('========== XOR ==========')
data = [(0,0,0),(0,0,1),(0,1,0),(0,1,1),(1,0,0),(1,0,1),(1,1,0),(1,1,1)]
for d in data:
  a0 = [d[0],d[1],d[2]]
  print('=========================')
  print('d =',d)
  #First Layer Values
  W1 = [[1,2,3],[4,2,2],[5,1,1]]
  b1 = [-2,-4,-5]

  a1 = []
  for j in range(len(W1)):
    a1.append(heaviside(sum(W1[i][j]*a0[i] for i in range(len(W1))) + b1[j]))

  print('1st Layer Activation')
  print('a_0^1 =',a1[0])
  print('a_1^1 =',a1[1])
  print('a_2^1 =',a1[2])

  #Second Layer Values
  W2 = [[3,1],[4,3],[6,6]]
  b2 = [-2,-4]
  a2 = []
  for j in range(len(W2[0])):
    a2.append(heaviside(sum(W2[i][j]*a1[i] for i in range(len(W2))) + b2[j]))

  print('Final Activation')
  print('a_0^2 =', a2[0])
  print('a_1^2 =', a2[1])
