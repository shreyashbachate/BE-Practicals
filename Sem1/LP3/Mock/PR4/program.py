# Define the function to minimize
def f(x):
 return (x + 3)**2
# Define the derivative of the function (gradient)
def df(x):
 return 2 * (x + 3)
# Parameters for gradient descent
learning_rate = 0.1 # Step size or learning rate
num_iterations = 100 # Number of iterations
x = 2 # Initial value of x
# Gradient Descent Algorithm
for i in range(num_iterations):
 gradient = df(x) # Calculate the gradient at the current point
 x = x - learning_rate * gradient # Update x using gradient descent formula
# After the iterations, x will contain the local minimum
local_minimum = f(x)
print("Local minimum at x =", x)
print("Minimum value =", local_minimum)