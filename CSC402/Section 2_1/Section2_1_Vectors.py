import numpy as np

# A vector is an 1-dimensional array of numbers.
# E.g., input hardness vector of our cat brain model
v = np.array([0.11, 0.01, 0.98, 0.12, 0.98, 0.85, 0.03,
              0.55, 0.49, 0.99, 0.02, 0.31, 0.55, 0.87,
              0.63])
print('Vector v =',v)
print('List v =',list(v))

# Individual elements of the vector can be accessed through the square bracket operator with indices of the desired element  within thosesquare brackets.
# Index starts from zero, not one.
first_element = v[0]
third_element = v[2]
print('First Element = {} Third Element = {}'.\
      format(first_element, third_element))


# Negative indices are to be counted from the end of array.
# E.g., -1 refers to the last array element.
#       -2 refers to the second from last element.
last_element = v[-1]
second_last_element = v[-2]
print('Last Element = {} Second to Last Element = {}'.\
      format(last_element, second_last_element))

# A range of elements can be sliced off a vector using the colon operator
second_to_fifth_elements = v[1:4]
print('Second to Fifth Elements: {}'.format(second_to_fifth_elements))

# If nothing is specified on the left of the arrow, it implies beginning of array.
# If nothing is specified after the  colon it implies end of array.
first_to_third_elements = v[:2]
last_two_elements = v[-2:]
print('First to Third: {}  Last Two Elements: {}'.\
      format(first_to_third_elements, last_two_elements))

# Size of the vector
num_elements_in_v = len(v)
print('Number of Elements in v: {}'.format(num_elements_in_v))
