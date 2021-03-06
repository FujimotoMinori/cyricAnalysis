import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm
 
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
  
x = y = np.arange(-20, 20, 0.5)
X, Y = np.meshgrid(x, y)
   
mu = np.array([3,1])
sigma = np.array([[10,0], [0,10]])
    
det = np.linalg.det(sigma)
inv_sigma = np.linalg.inv(sigma)
      
def f(x, y):
   x_c = np.array([x, y]) - mu
   return np.exp(- x_c.dot(inv_sigma).dot(x_c[np.newaxis, :].T) / 2.0) / (2*np.pi*np.sqrt(det))
               
Z = np.vectorize(f)(X,Y)
                
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.coolwarm)
plt.show()

