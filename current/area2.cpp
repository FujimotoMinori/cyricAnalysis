//just calcurate the ratio of chip area
//cant use the ratio of fraction of data

#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

static const int ECHARGE = 1.6*1.0e-19;

double ratio(){
  double xc,yc;
  double x,y;
  double sx,sy;
  double chip,window,offset;
  double r;	
  
	//[mm]
	xc = 20;
	yc = 11;
	x = 22;
	y = 14;
	sx = 3.0;
	sy = 3.0;
  
	chip = xc*yc;
	window = x*y;
	offset = x*y + 4*sx*sy + M_PI*sx*sy; 

    r = chip/offset;

	return r;	
}

int main(){
	double r;
	double s;
	double L;
	double current;
	double Sigma;
	double N;
	
	r = ratio(); 	
	std::cout << "r=" << r << std::endl;	

    //N = L*sigma
    /*	
        s = 2.0*1.1;//[cm]	
        current = 0.5*1.0e-9;	
        L = current/ECHARGE;   
        std::cout << "L=" << L << std::endl;	

        Sigma = 2.8*1.0e-14*8*1.0e4;
        std::cout << "Sigma=" << Sigma << std::endl;	

        N = L*Sigma;
        std::cout << "N=" << N << std::endl;	
     */

	return 0;
}



