import numpy as np

# A matrix can be viewed as a 2-dimensional array of numbers. It can be thought of as a collection of row vectors, or a collection of column vectors.

# For example, the training set for the cat-brain problem can be expressed as a matrix.
# Each input instance to the machine can be viewed as a vector represented by a row in this matrix.
# Our training set consists of 15 examples, where each example is a row vector of size 2. So there are 15 rows and 2 columns.

X = np.array([[0.11, 0.09], [0.01, 0.02], [0.98, 0.91], [0.12, 0.21],
              [0.98, 0.99], [0.85, 0.87], [0.03, 0.14], [0.55, 0.45],
              [0.49, 0.51], [0.99, 0.01], [0.02, 0.89], [0.31, 0.47],
              [0.55, 0.29], [0.87, 0.76], [0.63, 0.24]])
print('X = \n{}'.format(X))

# Shape of the matrix is depicted as a list.
# The first list element represents the number of rows,
# the second list element represents the number of columns.
# Our training set consists of 15 examples, where each example is a row vector of size 2. So the shape is [15, 2].
print('Shape of the matrix is: {}'.format(X.shape))



# Slicing the matrix
# The matrix can be sliced using the indices representing the axes. 

# Accessing individual elements of the matrix
# Each element is indexed by its row and column.
# Row, column indices start from 0

# Accessing first element of the matrix
first_element = X[0, 0]
print('First element X: {}'.format(first_element))

# Accessing 5th row, first column of the matrix
print('X[5][1]: {}'.format(X[5][1]))

# Accessing the rows
# Note the each row corresponds to one training example in our case.
# The : is shorthand to access all the elements of the selected rows
# i.e X[0, :] is equivalent of X[0, 0:num_columns]
row_1 = X[0, :] # First row has an index of 0
row_2 = X[1, 0:2] # Second row has an index of 1
print('Row 1: {} Shape: {}'.format(row_1, row_1.shape))
print('Row 2: {} Shape: {}'.format(row_2, row_2.shape))

# Accessing the columns
# The columns can similarly be accessed using the second axis.
# Note that each column corresponds to one feature i.e hardness or
# sharpness in our case.
column_1 = X[:, 0] # First column has an index of 0
column_2 = X[:, 1] #Second column has an index of 1
print('Column 1: {} Shape: {}'.format(column_1, column_1.shape))
print('Column 2: {} Shape: {}'.format(column_2, column_2.shape))

# Extracting sub-matrices. Slicing and dicing
# We can use a combination of row and column to
# slice and dice the matrix (i.e., extract sub-matrices).

# For example to access the first 3 training examples
first_3_training_examples = X[:3, ]
# X[:3, ] == X[0:3,] == X[:3, :] == X[:3, 0:num_columns]
# These are multiple ways to access the same elements.
print('First 3 training examples:\n{}'.format(first_3_training_examples))

# Selecting the hardness feature for  5th to 7th training examples
# Note that hardness corresponds to column 1
print('Hardness of 5-7 training examples is: {} '.format(X[5:8, 1]))