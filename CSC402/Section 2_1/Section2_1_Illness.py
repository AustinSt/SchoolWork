import numpy as np

def heaviside(x):
  if x >= 0:
    return 1
  return 0

def sigma(x):
  return 1/(1 + np.exp(-x))

X = np.array([
  [0,0,0,0,0],
  [0,0,0,0,1],
  [1,1,1,0,0],
  [1,0,0,1,0],
  [1,1,0,0,0],
  [1,0,1,0,0]])
#print('X =\n',X)

y = np.array([-1,1,1,-1,1,1])
#print('y =\n',y)

w = np.array([1,1,1,1,1])
b = -1
print(' ')
print('w = {} b = {}'.format(w,b))


print('Symptoms \t\t| Needed Output | x.w + b')
print('=============================================')
for i in range(len(y)):
  output = np.dot(X[i],w) + b
  print(X[i],'\t|', y[i], '\t\t\t|',output)


# X_mul_w_plus_b = np.matmul(X,w) + b
# print('Symptoms \t\t| Needed Output | X*w + b')
# print('=============================================')
# for i in range(len(y)):
#   output = round(X_mul_w_plus_b[i],3)
#   print(X[i],'\t|', y[i], '\t\t\t|',output)



# print('What should we select as w and b?')
# print('Denote A as the matrix X with a column of all ones at the end. Let wb denote the vector w with b appended to the end. The question now becomes can we find wb such that A*wb = y, i.e., wb = A^(-1)*y')
A = np.column_stack((X, np.ones(6)))
print('A =\n',A)

wb = np.matmul(np.linalg.inv(A), y)
print('wb =',wb) 

w = wb[:5]
b = wb[-1]
print(' ')
print('w = {} b = {}'.format(w,b))

print('Symptoms \t\t| Needed Output | x.w + b')
print('=============================================')
for i in range(len(y)):
  output = round(np.dot(X[i],w) + b,3)
  print(X[i],'\t|', y[i], '\t\t\t|',output)