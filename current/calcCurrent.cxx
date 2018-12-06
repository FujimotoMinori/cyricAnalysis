/*
   calcurate the ratio of flux on pixelarea(target) 
 */

#include <iostream>
#include <cmath>

using namespace std;

int calcCurrent(){
    double wx,wy,h;
    double cx,cy;
    double ewx,ewy;
    double gauss;
    double V1,V2,V3,V4;
    double RV;
    double pi = 3.141592;
    double answer;
    double eanswer;

    wx = 34.;
    wy = 26.;
    cx = 20.;
    cy = 9.6;
    ewx = 1.0e-3;
    ewy = 1.0e-3;
    h = 10.;

    gauss = 3.96;

    RV = cx*cy*h;
    V1 = wx*wy*h; 
    V2 = wx*gauss; 
    V3 = gauss*wy; 
    V4 = gauss*pi; 

    answer = RV/(V1+V2+V3+V4);
    double a;
    a = RV/pow(V1+V2+V3+V4,2);
    eanswer = a*sqrt(pow(wy*h+gauss,2)*ewx*ewx+pow(wx*h+gauss,2)*ewy*ewy);

    std::cout << "answer=" << answer << " error= " << eanswer << std::endl;

    return 0;	
}


