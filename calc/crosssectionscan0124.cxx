/*
  crosssectionscan0124.cxx
  calcurate cross section of irradiation by scanning
  the error 
*/

#include <iostream>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES
using namespace std;

static const double ECHARGE = 1.6*1.0e-19;
static const double X = 2.0;
static const double Y = 0.96;
static const double AllPixel = 491520;

void crosssectionscan0124(){

    std::cout << "run34" << std::endl; 
    double Time = 1145;
    double N = 9378;
    double Current = 1.15*1.0e-9;
    double eCurrent = 0.13*1.0e-9;
    double ratio = 0.242; 
    double eratio = 0.01;


    //double eN = sqrt(N);
    double eN = sqrt(N);
    double Fraction = Current*ratio; 
    double eFraction = sqrt(TMath::Power(eCurrent*ratio,2)+TMath::Power(Current*eratio,2)); 
    double S = X*Y;
    double L,eL;
    double F,eF;
    double Fxtime,eFxtime;
    double Sigma,eSigma;
    double SigmaPixel,eSigmaPixel;

    L = Fraction/ECHARGE;   
    eL = eFraction/ECHARGE;   
    std::cout << "L=" << L << " +- " << eL << std::endl; 

    //(i)
    std::cout << "N=" << N << " +- " << eN << std::endl; 

    //(ii)
    F = Fraction/ECHARGE/S;  
    eF = eFraction/ECHARGE/S;  
    std::cout << "F=" << F << " +- " << eF << std::endl; 
    Fxtime = F*Time; 
    eFxtime = eF*Time;
    std::cout << "Fxtime=" << Fxtime << " +- " << eFxtime << std::endl; 

    Sigma = N/Fxtime;
    eSigma = sqrt(TMath::Power(Fxtime*eN,2)+TMath::Power(N*eFxtime,2))/TMath::Power(Fxtime,2); 
    std::cout << "Sigma=" << Sigma << " +- " << eSigma << std::endl; 

    SigmaPixel = Sigma/AllPixel;
    eSigmaPixel = eSigma/AllPixel;
    std::cout << "SigmaPixel=" << SigmaPixel << " +- " << eSigmaPixel << std::endl; 
    
    return;
}

