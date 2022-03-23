def heaviside(x):
  if x >= 0:
    return 1
  else:
    return 0

print('=========================')
print('========== XOR ==========')
data = [(0,0),(0,1),(1,0),(1,1)]
for d in data:
  x_0 = d[0]
  x_1 = d[1]
  print('=========================')
  print('d =',d)
  #First Layer Values
  w_0_0_1 = -2 #w_start_end_layer
  w_0_1_1 = 2
  w_1_0_1 = -2
  w_1_1_1 = 2
  b_0_1 = 3
  b_1_1 = -1

  a_0_1 = heaviside(w_0_0_1*x_0 + w_1_0_1*x_1 + b_0_1)
  a_1_1 = heaviside(w_0_1_1*x_0 + w_1_1_1*x_1 + b_1_1)
  print('1st Layer Activation')
  print('a_0_1 =',a_0_1)
  print('a_1_1 =',a_1_1)

  #Second Layer Values
  w_0_0_2 = 2      
  w_1_0_2 = 2
  b_0_2 = -3
  a_0_2 = heaviside(w_0_0_2*a_0_1 + w_1_0_2*a_1_1 + b_0_2)
  print('Final Activation')
  print('a_0_2 =', a_0_2)
  print(x_0, 'XOR' ,x_1, '=', x_0 ^ x_1)
  print('Did it work?', a_0_2 == (x_0 ^ x_1))