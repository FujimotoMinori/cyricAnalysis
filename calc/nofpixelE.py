#coding:utf-8

#count the # of pixels in beam flux

import numpy as np
import matplotlib.pyplot as plt

sx = 3.88;
sy = 5.24;

def is_innerRD53A(x,y):
    return -10<=x<=10 and -5<=y<=5 

def is_innerSync(x,y):
    return -10<=x<=-3.6 and -5<=y<=5 
def is_innerLin(x,y):
    return -3.6<x<=3.2 and -5<=y<=5 
def is_innerDiff(x,y):
    return 3.2<x<=10 and -5<=y<=5 

def is_inner(x,y):
    return (x**2/(sx*2)**2)+(y**2/(sy*2)**2) < 1 


inner_points_cnt = 0
all_points_cnt = 0
sync_points_cnt = 0
lin = 0
diff = 0

x1 = np.random.rand(100000) * (10+10) -10
y1 = np.random.rand(100000) * (5+5) -5

for x, y in zip(x1, y1):
    if is_innerRD53A(x, y):
       all_points_cnt += 1
       if is_inner(x, y):
           inner_points_cnt += 1
           if is_innerSync(x, y):
               sync_points_cnt += 1
           if is_innerLin(x, y):
               lin += 1
           if is_innerDiff(x, y):
               diff += 1

ratio = (inner_points_cnt / all_points_cnt)
pixel = 491520 * ratio 

sratio = (sync_points_cnt / all_points_cnt)
spixel = 491520 * sratio 
lratio = (lin / all_points_cnt)
lpixel = 491520 * lratio 
dratio = (diff / all_points_cnt)
dpixel = 491520 * dratio 

fpixel = (pixel-spixel)+spixel/8*3

print("all points cnt")
print(all_points_cnt)
print("inner points cnt")
print(inner_points_cnt)
print("sync points cnt")
print(sync_points_cnt)
print("ratio inside")
print(ratio)
print("ratio Sync.")
print(sratio)
print("number of pixels inside the beam")
print(pixel)
print("number Sync.")
print(spixel)
print("number Lin.")
print(lpixel)
print("number Diff.")
print(dpixel)
print("# of all pixel")
print(spixel+lpixel+dpixel)
print("real number of pixel inside the beam")
print(fpixel)

#plt.figure(facecolor="w")
#plt.scatter(x1,y1,color='r',marker='x',label="$mu = 3.0$")
#
#plt.figtext(0.8,0.6,"$R_1$",size=20)
#plt.xlabel('$x$',size=10)
#plt.ylabel('$y$',size=10)
#
#plt.gca().set_aspect('equal', adjustable='box')
#  
#plt.axis([-10.0,10.0,-5.0,5.0],size=20)
#plt.grid(True)
#plt.legend()
#
#plt.savefig("multivariate_normal.png",format = 'png', dpi=200)
#plt.show()
#plt.close()

