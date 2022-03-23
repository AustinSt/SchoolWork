def heaviside(x):
  if x >= 0:
    return 1
  else:
    return 0

print('=========================')
print('========== XOR ==========')
data = [(0,0),(0,1),(1,0),(1,1)]
for d in data:
  a0 = [d[0],d[1]]
  print('=========================')
  print('d =',d)
  #First Layer Values
  W1 = [[-2,2],[-2,2]]
  b1 = [3,-1]

  a1 = [0,0]
  a1[0] = heaviside(sum(W1[i][0]*a0[i] for i in range(2)) + b1[0])
  a1[1] = heaviside(sum(W1[i][1]*a0[i] for i in range(2)) + b1[1])

  print('1st Layer Activation')
  print('a_0^1 =',a1[0])
  print('a_1^1 =',a1[1])

  #Second Layer Values
  W2 = [[2],[2]]
  b2 = [-3]
  a2 = [0]
  a2[0] = heaviside(sum(W2[i][0]*a1[i] for i in range(2)) + b2[0])

  print('Final Activation')
  print('a_0^2 =', a2[0])
  print(a0[0], 'XOR' ,a0[1], '=', a0[0] ^ a0[1])
  print('Did it work?', a2[0] == (a0[0] ^ a0[1]))


  