import numpy as np

def heaviside(x):
  if x >= 0:
    return 1
  return 0

def sigma(x):
  return 1/(1 + np.exp(-x))

def inverse(A):
  if np.linalg.det(A) == 0:
    return False
  return np.linalg.inv(A)

def pseudo_inverse(A):
    return np.matmul(np.linalg.inv(np.matmul(np.transpose(A), A)), np.transpose(A))

#########################################
########         AND  v2         ########
#########################################

X = np.array([
  [0,0],
  [0,1],
  [1,0],
  [1,1]])
#print('X =\n',X)

y = np.array([1,1,1,-1])
#print('y =\n',y)

A = np.column_stack((X, np.ones(len(X))))
wb = np.matmul(pseudo_inverse(A), y)

w = wb[:2]
b = wb[-1]
print(' ')
print('w = {} b = {}'.format(w,b))

print('Inputs \t| Needed Output | x.w + b | h(x.w + b)')
print('=============================================')
for i in range(len(y)):
  output = round(np.dot(X[i],w) + b,3)
  print(X[i],'\t|', y[i], '\t\t\t|',output,'\t  |',heaviside(output))

#########################################
######## SYMPTOMS AND ILLNESS v2 ########
#########################################

X = np.array([
  [0,0,0,0,0],
  [0,0,0,0,1],
  [1,1,1,0,0],
  [1,0,1,1,0],
  [0,1,1,0,1],
  [1,0,1,0,0],
  [1,0,0,1,0],
  [1,1,1,1,0],
  [1,0,0,1,1],
  [1,1,1,1,1]])
#print('X =\n',X)

y = np.array([-1,1,-1,1,1,1,-1,1,1,0])
#print('y =\n',y)

w = np.array([-1,-1,2,1,2])
b = -1
print(' ')
print('w = {} b = {}'.format(w,b))


print('Symptoms \t\t| Needed Output | x.w + b | h(x.w + b)')
print('=======================================================')
sum_squares_error = 0
for i in range(len(y)):
  output = round(np.dot(X[i],w) + b,3)
  sum_squares_error = (output - y[i])**2
  print(X[i],'\t|', y[i], '\t\t\t|',output, '\t  |',heaviside(output))
print('Sum of Squares Error =',sum_squares_error)


A = np.column_stack((X, np.ones(len(X))))
wb = np.matmul(pseudo_inverse(A), y)

w = wb[:5]
b = wb[-1]
print(' ')
print('w = {} b = {}'.format(w,b))

print('Symptoms \t\t| Needed Output | x.w + b | h(x.w + b)')
print('=======================================================')
sum_squares_error = 0
for i in range(len(y)):
  output = round(np.dot(X[i],w) + b,3)
  sum_squares_error = (output - y[i])**2
  print(X[i],'\t|', y[i], '\t\t\t|',output, '\t  |',heaviside(output))
print('Sum of Squares Error =',sum_squares_error)