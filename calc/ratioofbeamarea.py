#coding:utf-8

import numpy as np
import matplotlib.pyplot as plt

def is_innerRD53A(x,y):
    return -10<x<10 and -5<y<5 

def is_inner(x,y):
    return x**2+y**2 < 9 


xmu = np.random.rand(100000) * (10+10) -10
ymu = np.random.rand(100000) * (5+5) -5

for x, y in zip(xmu, ymu):
    mu1 = [x,y]

#mu1 = [0,0]
cov = [[3,0],[0,3]]

inner_points_cnt = 0
all_points_cnt = 0

x1,y1 = np.random.multivariate_normal(mu1,cov,100000).T

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

