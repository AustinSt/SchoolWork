import numpy as np

X = np.array([[0.11, 0.09], [0.01, 0.02], [0.98, 0.91], [0.12, 0.21],
              [0.98, 0.99], [0.85, 0.87], [0.03, 0.14], [0.55, 0.45],
              [0.49, 0.51], [0.99, 0.01], [0.02, 0.89], [0.31, 0.47],
              [0.55, 0.29], [0.87, 0.76], [0.63, 0.24]])

y = np.array([-0.8, -0.97, 0.89, -0.67, 0.97, 0.72, -0.83, 0.00, 0.00,
              0.00, -0.09, -0.22, -0.16, 0.63, 0.37])

print('(Hard, Sharp) | Threat')
print('======================================')
for i in range(len(y)):
  print(X[i],'  |',y[i])

w = np.array([1,1])
b = -1

#w = np.array([1.07661761, 0.89761672])
#b = -0.95816936

print(' ')
print('w = {} b = {}'.format(w,b))
print('(Hard, Sharp) | x.w + b \t| Threat')
print('========================================')
sum_squares_error = 0
for i in range(len(y)):
  output = round(np.dot(w,X[i]) + b,3)
  sum_squares_error += (output - y[i])**2
  print(X[i],'  |',output, '\t\t|',y[i])
print('sum_squares_error',sum_squares_error)


# print(' ')
# print('w = {} b = {}'.format(w,b))
# X_mul_w_plus_b = np.matmul(X,w) + b
# print('(Hard, Sharp) | X*w + b\t\t| Threat')
# print('========================================')
# error_squared = 0
# for i in range(len(y)):
#   output = round(X_mul_w_plus_b[i],3)
#   error_squared += (output - y[i])**2
#   print(X[i],'  |',output, '\t\t|',y[i])
# print('Sum Error Squared =',error_squared)


# print('What should we select as w and b?')
# print('Denote A as the matrix X with a column of all ones at the end. Let wb denote the vector w with b appended to the end. The question now becomes can we find wb such that A*wb = y. In this example A is not a square matrix, so simply using an inverse will blow up in our face. We can however use a pseudoinverse')

def pseudo_inverse(A):
    return np.matmul(np.linalg.inv(np.matmul(np.transpose(A), A)), np.transpose(A))

A = np.column_stack((X, np.ones(15)))
wb = np.matmul(pseudo_inverse(A), y)

w = wb[:2]
b = wb[-1]

print(' ')
print('w = {} b = {}'.format(w,b))
print('(Hard, Sharp) | x.w + b \t| Threat')
print('========================================')
sum_squares_error = 0
for i in range(len(y)):
  output = round(np.dot(w,X[i]) + b,3)
  sum_squares_error += (output - y[i])**2
  print(X[i],'  |',output, '\t\t|',y[i])
print('sum_squares_error',sum_squares_error)
