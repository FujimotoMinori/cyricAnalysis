/*
  calcurate cross section of irradiation by scanning
*/

#include <iostream>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

static const double ECHARGE = 1.6*1.0e-19;
static const double X = 2.0;
static const double Y = 0.96;
static const double AllPixel = 491520;

int main(){

    double Time = 594;
    double N = 4712;

    double Current = 1.0*1.0e-9;
    double Fraction = Current*0.59;
    double beamsize = 0.3;
    double S = X*Y;
    std::cout << "S= " << S << std::endl; 
    double AllPixel = 491520;
    double L;
    double F;
    double Fxtime;
    double Sigma;
    double NPixel;
    double SigmaPixel;

    L = Fraction/ECHARGE;   
    std::cout << "L= " << L << std::endl; 

    //(i)
    std::cout << "N= " << N << std::endl; 

    //(ii)
    F = Fraction/ECHARGE/S;  
    std::cout << "F= " << F << std::endl; 
    Fxtime = F*Time; 
    std::cout << "Fxtime= " << Fxtime << std::endl; 

    Sigma = N/Fxtime;
    std::cout << "Sigma= " << Sigma << std::endl; 

    NPixel = AllPixel; 
    std::cout << "AllPixel= " << AllPixel << std::endl; 

    SigmaPixel = Sigma/NPixel;
    std::cout << "SigmaPixel= " << SigmaPixel << std::endl; 
    return 0;

}

