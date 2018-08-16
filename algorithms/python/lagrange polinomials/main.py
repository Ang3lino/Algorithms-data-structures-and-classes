# pip3 install matplotlib

import matplotlib.pyplot as plt
import numpy as np

from LagrangePolynomial import *

x = [ 2, 11 / 4, 4 ]
y = [ 1 / 2, 4 / 11, 1 / 4 ]
print(x)
lpol = LagrangePolynomial() 
lpol.set_points(x, y)

count = 0
a = []
b = []
for xi in x:
    b.append(lpol.evaluate(xi))
    a.append(xi)
    count += 1
plt.scatter(a, b)

print('v:')
plt.show()
