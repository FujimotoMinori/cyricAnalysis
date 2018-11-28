#coding:utf-8

import numpy as np
import matplotlib.pyplot as plt

def is_inner(x,y):
    return x**2+y**2 < 9 

mu1 = [0,0]
cov = [[3,0],[0,3]]

inner_points_cnt = 0
all_points_cnt = 0

const = 1.0*10**15
#x1,y1 = np.random.multivariate_normal(mu1,cov,1000000).T
values = np.random.multivariate_normal(mu1,cov,1000000)
x=values[:,0]
y=values[:,1]
#y=const+5.6*10**12*values[:,1]

fig = plt.figure()
ax = fig.add_subplot(111)

H = ax.hist2d(x,y,bins=[np.linspace(-10,10,100),np.linspace(-5,5,50)])
ax.set_title('distribution')
ax.set_xlabel('x')
ax.set_ylabel('y')
fig.colorbar(H[3],ax=ax)
plt.axis([-10.0,10.0,-5.0,5.0],size=20)
plt.show()
plt.close()

