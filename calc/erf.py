#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import math
from scipy.special import erf
from scipy.integrate import quad
import scipy.integrate as integrate

def integrand(t, alpha, r ):
    return np.exp(-alpha*(t-r)**2)

def damp(alpha, rho, r):
    return quad(integrand, 0, rho, args=(alpha, r))[0]

def norm_constant(alpha, r):
    return 2.0*math.sqrt(2)/math.sqrt(math.pi) * (1./(1.- erf(-math.sqrt(np.abs(alpha))*r)))

A = 1.5
r = 0.3

g = [ norm_constant(A,r) *damp(A,x,r) for x in np.arange(-2,2,0.2)]
x = np.arange(-2,2,0.2)

plt.plot(x,g,'r')
plt.show()

