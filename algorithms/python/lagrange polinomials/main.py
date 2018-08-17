""" 
    La aplicacion corre en python3, en python2 puede fallar. Instalalo con
        sudo apt install python3
    Depende de matplotlib, instalala con:
        pip3 install matplotlib
    Para correr:
        python3 main.py LagrangePolynomial.py 
        python main.py LagrangePolynomial.py (si la primera no funciona)
    Nota: Basta que en una lista de enteros se encuentre un flotante para que 
    cada elemento sea del tipo float.
"""

import matplotlib.pyplot as plt
import numpy as np

from LagrangePolynomial import *
from random import * # randint function definition

b = int(10 * float(input("ultimo valor del voltaje: ")) +  2)
x = [ n / 10 for n in range(0, b, 2) ]
y = list()
diodetag = input("Nombre del diodo: ")
#for i in x:
#    y.append(float(input("v[{}] = ".format(i))))
y = [ randint(1, 10) / randint(1, 20) for i in range(len(x)) ] # for testing

print(list( zip(x, y) ))

lpol = LagrangePolynomial() 
lpol.set_points(x, y)

scale = 1000
x = [ i / scale  for i in range(int(scale * x[-1])) ]
y = [ lpol.evaluate(xi) for xi in x ]

plt.plot(x, y)
plt.title("Grafica del diodo")
plt.xlabel("Voltaje (v)")
plt.ylabel("Corriente (mA)")
plt.legend([diodetag])
plt.show()
