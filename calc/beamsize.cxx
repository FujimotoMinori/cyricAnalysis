/*
   calcurate beam size at slot10 from data of finger 
 */

#include <iostream>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

int main(){

    double y1,y2 = 0.;
    double ey1,ey2 = 0.;

    double x1 = 1.;
    double x2 = 15.;

    double a,b,ea,eb;
    double answer,eanswer;
    
    //beamsize [mm]
    /*
    double upXcircle = 2.71;
    double eupXcircle = 0.26;
    double upXbar = 2.66;
    double eupXbar = 0.10;

    double downXcircle = 4.66;
    double edownXcircle = 1.28;
    double downXbar = 4.83;
    double edownXbar = 0.41;
    */

    double upXcircle = 3.60;
    double eupXcircle = 0.54;
    double upXbar = 3.85;
    double eupXbar = 0.19;

    double downXcircle = 5.29;
    double edownXcircle = 2.04;
    double downXbar = 4.83;
    double edownXbar = 0.47;

    y1 = (upXcircle + upXbar)/2.; 
    std::cout << "eupXcircle = " << eupXcircle << std::endl;
    ey1 = (0.5)*sqrt(eupXcircle*eupXcircle+eupXbar*eupXbar);
    ey1 = (0.5)*sqrt(0.26*0.26+0.1*0.1);


    y2 = (downXcircle + downXbar)/2.; 
    ey2 = (0.5)*sqrt(edownXcircle*edownXcircle+edownXbar*edownXbar);
    std::cout << "meanUp = " << y1 << " +- " << ey1 << std::endl;
    std::cout << "meanDown = " << y2 << " +- " << ey2 << std::endl;

    a = (y2-y1)/(x2-x1);
    ea = sqrt(ey1*ey1+ey2*ey2)/(x2-x1); 
    b = (x2*y1-x1*y2)/(x2-x1);
    eb = sqrt(pow(x2*ey1,2)+pow(x1*ey2,2))/(x2-x1);

    answer = a*10+b;
    eanswer = sqrt(10*10*ea*ea+eb*eb); 
    std::cout << "answer = " << answer << " +- " << eanswer << std::endl;

}

