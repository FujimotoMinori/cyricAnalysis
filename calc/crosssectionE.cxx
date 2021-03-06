/*
  calcurate cross section of one point irradiation
  consider the shape of the beam as elips
*/

#include <iostream>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

static const double ECHARGE = 1.6*1.0e-19;
static const double X = 2.0; //[cm]
static const double Y = 0.96; //[cm]
static const double AllPixel = 491520;

int main(){

    std::cout << "run45" << std::endl; 
    double Time = 300;
    double N = 10627;
    double Current = 0.99*1.0e-9; //[A]
    double eCurrent = 0.09*1.0e-9; //[A]
    double beamsizex = 0.379; //[cm]
    double beamsizez = 0.499; //[cm]
    double ebeamsizex = 0.003; //[cm]
    double ebeamsizez = 0.019; //[cm]
    double NPixel = 295636;

    double eN = sqrt(N);
    double S = M_PI*(2*beamsizex)*(2*beamsizez);
    double eS = M_PI*4*sqrt(pow(beamsizez*ebeamsizex,2)+pow(beamsizex*ebeamsizez,2));
    double L,eL;
    double F,eF;
    double Fxtime,eFxtime;
    double Sigma,eSigma;
    double SigmaPixel,eSigmaPixel;

    L = Current/ECHARGE;   
    eL = eCurrent/ECHARGE; 
    std::cout << "L=" << L << " +- " << eL << std::endl; 
    std::cout << "S=" << S << " +- " << eS << std::endl; 

    //(i)
    std::cout << "N=" << N << " +- " << eN << std::endl; 

    //(ii)
    F = Current*0.98/ECHARGE/S;  
    eF = (0.98/ECHARGE/S/S)*sqrt(pow(S*eCurrent,2)+pow(Current*eS,2));  
    std::cout << "F=" << F << " +- " << eF << std::endl; 
    Fxtime = F*Time; 
    eFxtime = eF*Time;
    std::cout << "Fxtime=" << Fxtime << " +- " << eFxtime << std::endl; 

    Sigma = N/Fxtime;
    eSigma = sqrt(pow(Fxtime*eN,2)+pow(N*eFxtime,2))/pow(Fxtime,2); 
    std::cout << "Sigma=" << Sigma << " +- " << eSigma << std::endl; 

    std::cout << "AllPixel=" << AllPixel << std::endl; 
    std::cout << "NPixel=" << NPixel << std::endl; 

    SigmaPixel = Sigma/NPixel;
    eSigmaPixel = eSigma/NPixel;
    std::cout << "SigmaPixel=" << SigmaPixel << " +- " << eSigmaPixel << std::endl; 

    return 0;

}

