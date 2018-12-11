#coding:utf-8

#1.count the # of pixels in beam flux
#2.get the ratio of beam flux inside the chip?
#consider the beam shape as elips

import numpy as np
import matplotlib.pyplot as plt

sx = 3.8
sz = 5.2 

def is_innerRD53A(x,y):
    return -10<x<10 and -5<y<5 

def is_inner(x,y):
    return (x**2/(sx*2)**2)+(y**2/(sz*2)**2) < 1 

mu1 = [0,0]
cov = [[3.8,0],[0,5.2]]

inner_points_cnt = 0
all_points_cnt = 0
sync_points_cnt = 0

x1,y1 = np.random.multivariate_normal(mu1,cov,1000000).T

for x, y in zip(x1, y1):
    if is_innerRD53A(x, y):
       all_points_cnt += 1
       if is_inner(x, y):
           inner_points_cnt += 1

ratio = (inner_points_cnt / all_points_cnt)

print(all_points_cnt)
print(inner_points_cnt)
print(ratio)

plt.figure(facecolor="w")
plt.scatter(x1,y1,color='r',marker='x',label="$mu = 3.0$")

#plt.figtext(0.8,0.6,"$R_1$",size=20)
plt.xlabel('$x$',size=10)
plt.ylabel('$y$',size=10)

plt.gca().set_aspect('equal', adjustable='box')
  
plt.axis([-10.0,10.0,-5.0,5.0],size=20)
plt.grid(True)
plt.legend()

#plt.savefig("multivariate_normal.png",format = 'png', dpi=200)
plt.show()
plt.close()

