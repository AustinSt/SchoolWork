def heaviside(x):
  if x >= 0:
    return 1
  else:
    return 0

def sigma(x):
  return 1/(1 + 2.71828**(-x))

data = [(0,0,0,0,0),(0,0,0,0,1),(0,0,0,1,0),(0,0,0,1,1),(0,0,1,0,0),(0,0,1,0,1),(0,0,1,1,0),(0,0,1,1,1),(0,1,0,0,0),(0,1,0,0,1),(0,1,0,1,0),(0,1,0,1,1),(0,1,1,0,0),(0,1,1,0,1),(0,1,1,1,0),(0,1,1,1,1),(1,0,0,0,0),(1,0,0,0,1),(1,0,0,1,0),(1,0,0,1,1),(1,0,1,0,0),(1,0,1,0,1),(1,0,1,1,0),(1,0,1,1,1),(1,1,0,0,0),(1,1,0,0,1),(1,1,0,1,0),(1,1,0,1,1),(1,1,1,0,0),(1,1,1,0,1),(1,1,1,1,0),(1,1,1,1,1)]

w = [2,6,4,2,10] #Change these values and rerun
b = -9 #Change this value and rerun

print('==========================================================================')
print('Weights and Bias Values')
print('w0 =',w[0],'| w1 =',w[1],'| w2 =',w[2],'| w3 =',w[3],'| w4 =',w[4],'| b =',b)

print(' ')
print('Data Point  \t | w.x + b \t| h(w.x + b)')
print('========================================')
true_counter = 0
for d in data:
  print(d,' | ',sum(w[i]*d[i] for i in range(5)) + b,'\t\t|',heaviside(sum(w[i]*d[i] for i in range(5)) + b))
  #Use heaviside for Perceptrons
  #Use sigma for Sigmoid Neurons
  if sigma(sum(w[i]*d[i] for i in range(5)) + b) >= 0.99:
    true_counter += 1
    #For Sigmoid Neurons change == 1 to some upper bound, e.g., > 0.8
print('Number True/1/Positive?',true_counter)
  


print('')
print('==========================================================================')
print('Training Data!')
print('==========================================================================')
training_data = [
[(0,0,0,0,0),0],
[(0,0,0,0,1),1],
[(1,1,1,0,0),1],
[(1,0,0,1,0),0],
[(1,1,0,0,0),1],
[(1,0,1,0,0),1]]

print('Data Point  \t | Needed Output | Current Output (w.x + b) and h(w.x + b)')
print('==========================================================================')
for td in training_data:
  print(td[0], ' | \t\t',td[1], ' \t |',sum(w[i]*td[0][i] for i in range(5)) + b,' -> ', sigma(sum(w[i]*td[0][i] for i in range(5)) + b))
  #Use heaviside for Perceptrons
  #Use sigma for Sigmoid Neurons
