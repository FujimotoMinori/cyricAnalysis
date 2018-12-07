/*
  calcurate cross section of one point irradiation
  run44
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
    double Time = 240;
    double N = 5654;
    double eN = sqrt(N);
    double Current = 0.92*1.0e-9;
    double eCurrent = 0.09*1.0e-9;
    double beamsize = 0.30; //[cm]
    //double ebeamsize = 
    double S = M_PI*(2*beamsize)*(2*beamsize);

    double L,eL;
    double F,eF;
    double Fxtime,eFxtime;
    double Sigma,eSigma;
    double NPixel;
    double SigmaPixel,eSigmaPixel;

    L = Current/ECHARGE;   
    eL = eCurrent/ECHARGE; 
    std::cout << "L=" << L << " +- " << eL << std::endl; 
    std::cout << "S=" << S << std::endl; 

    //(i)
    std::cout << "N=" << N << " +- " << eN << std::endl; 

    //(ii)
    F = Current*0.95/ECHARGE/S;  
    eF = eCurrent*0.95/ECHARGE/S;  
    std::cout << "F=" << F << " +- " << eF << std::endl; 
    Fxtime = F*Time; 
    eFxtime = eF*Time;
    std::cout << "Fxtime=" << Fxtime << " +- " << eFxtime << std::endl; 

    Sigma = N/Fxtime;
    eSigma = sqrt(pow(Fxtime*eN,2)+pow(N*eFxtime,2))/pow(Fxtime,2); 
    std::cout << "Sigma=" << Sigma << " +- " << eSigma << std::endl; 

    NPixel = AllPixel * 0.51; 
    std::cout << "AllPixel=" << AllPixel << std::endl; 
    std::cout << "NPixel=" << NPixel << std::endl; 

    SigmaPixel = Sigma/NPixel;
    eSigmaPixel = eSigma/NPixel;
    std::cout << "SigmaPixel=" << SigmaPixel << " +- " << eSigmaPixel << std::endl; 

    return 0;

}

