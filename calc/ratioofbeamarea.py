#coding:utf-8

import numpy as np
import matplotlib.pyplot as plt

sx = 3.8
sz = 4.5 
startx = -17
startz = -13

def is_innerRD53A(x,y):
    return -10<x<10 and -5<y<5 

def is_innerpixel(x,y):
    return -10<x<10 and -4.8<y<4.8 

mu1 = [0,0]
point = [0,0]
cov = [[sx,0],[0,sz]]

inner_points_cnt = 0
all_points_cnt = 0

xmu = 0
zmu = 0
i = 0
j = 0
n = 0
x1 = []
y1 = []

while xmu <= 17:
    i += 1
    xmu = startx + 1*i
    print(i)
    while zmu <= 13:
        j += 1 
        zmu = startz + 1*j
        print(j)
        mu1 = [xmu,zmu]
        print(mu1)
        xtemp,ytemp = np.random.multivariate_normal(mu1,cov,3).T
        #if is_innerpixel(xtemp, xtemp):
        #    inner_points_cnt += 1

x1,y1 = np.random.multivariate_normal(mu1,cov,1000000).T

for x, y in zip(x1, y1):
    all_points_cnt += 1
    if is_innerpixel(x, y):
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
  
plt.axis([-20.0,20.0,-10.0,10.0],size=20)
plt.grid(True)
plt.legend()

#plt.savefig("multivariate_normal.png",format = 'png', dpi=200)
plt.show()
plt.close()

