#coding:utf-8

import numpy as np
import matplotlib.pyplot as plot

mu1 = [0,0]
#mu2 = [2,2]
cov = [[0,3],[3,0]]

x1,y1 = np.random.multivariate_normal(mu1,cov,50000).T
#x2,y2 = np.random.multivariate_normal(mu2,cov,500).T

plot.figure(facecolor="w")

plot.scatter(x1,y1,color='r',marker='x',label="$K_1,mu_1$")
#plot.scatter(x2,y2,color='b',marker='x',label="$K_2,mu_2$")

#plot.figtext(0.8,0.6,"$R_1$",size=20)
#plot.figtext(0.2,0.3,"$R_2$",size=20)

#plot.xlabel('$x$',size=20)
#plot.ylabel('$y$',size=20)

plot.axis([-10.0,10.0,-10.0,10.0],size=20)
plot.grid(True)
plot.legend()

#plot.savefig("multivariate_normal.png",format = 'png', dpi=200)
plot.show()
plot.close()


