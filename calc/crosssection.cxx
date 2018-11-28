/*
  calcurate cross section of one point irradiation
*/

#include <iostream>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

static const double ECHARGE = 1.6*1.0e-19;
static const double X = 0.20;
static const double Y = 0.11;

int main(){

    double Time = 180;
    double N = 4245;

    double Current = 1.0*1.0e-9;
    double beamsize = 0.3;
    double S = M_PI*(2*beamsize)*(2*beamsize);
    double AllPixel = 491520;
    double L;
    double F;
    double Fxtime;
    double Sigma;
    double NPixel;
    double SigmaPixel;

    L = Current/ECHARGE;   
    std::cout << "L=" << L << std::endl; 

    //(i)
    std::cout << "N=" << N << std::endl; 

    //(ii)
    F = Current/ECHARGE/S;  
    std::cout << "F=" << F << std::endl; 
    Fxtime = F*Time; 
    std::cout << "Fxtime=" << Fxtime << std::endl; 

    Sigma = N/Fxtime;
    std::cout << "Sigma=" << Sigma << std::endl; 

    NPixel = AllPixel * 0.51; 
    std::cout << "AllPixel=" << AllPixel << std::endl; 

    SigmaPixel = Sigma/NPixel;
    std::cout << "SigmaPixel=" << SigmaPixel << std::endl; 
    return 0;

}

