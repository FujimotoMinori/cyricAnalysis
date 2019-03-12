/*
  crosssectionscanseparate.cxx
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

void crosssectionscan_separate(){

    std::cout << "all" << std::endl; 
    int nrun = 4;
    double Time[4] = {458,594,594,594};
    double N[4] = {3461,4562,4712,5271};
    double Current[4] = {1.01*1.0e-9,1.06*1.0e-9,1.10*1.0e-9,1.11*1.0e-9};
    double eCurrent = 0.05*1.0e-9;
    double ratio = 0.242; 
    double eratio = 0.01;


    double S = X*Y;
    double eN[4];
    double Fraction[4];  
    double eFraction[4];
    double L[4],eL[4];
    double F[4],eF[4];
    double Fxtime[4],eFxtime[4];
    double Sigma[4],eSigma[4],eSigma2[4];
    double SigmaPixel[4],eSigmaPixel[4],eSigmaPixel2[4];

    double allN = 0.;
    double alleN = 0.;
    double allFxtime = 0.;
    double allSigma = 0.;
    double alleSigma = 0.;
    double allSigmaPixel = 0.;
    double alleSigmaPixel= 0.;

    for(int i=0;i<nrun;i++){
        eN[i] = sqrt(N[i]);
        Fraction[i] = Current[i]*ratio;
        eFraction[i] = sqrt(TMath::Power(eCurrent*ratio,2)+TMath::Power(Current[i]*eratio,2)); 
        L[i] = Fraction[i]/ECHARGE;   
        eL[i] = eFraction[i]/ECHARGE;   
        std::cout << "L=" << L[i] << " +- " << eL[i] << std::endl; 
        //(i)
        std::cout << "N=" << N[i] << " +- " << eN[i] << std::endl; 
        //(ii)
        F[i] = Fraction[i]/ECHARGE/S;  
        eF[i] = eFraction[i]/ECHARGE/S;  
        std::cout << "F=" << F[i] << " +- " << eF[i] << std::endl; 
        Fxtime[i] = F[i]*Time[i]; 
        eFxtime[i] = eF[i]*Time[i];
        std::cout << "Fxtime=" << Fxtime[i] << " +- " << eFxtime[i] << std::endl; 
        Sigma[i] = N[i]/Fxtime[i];
        eSigma[i] = eN[i]/Fxtime[i]; 
        eSigma2[i] = (N[i]/(Fxtime[i]*Fxtime[i]))*eFxtime[i]; 
        //eSigma[i] = sqrt(TMath::Power(Fxtime[i]*eN[i],2)+TMath::Power(N[i]*eFxtime[i],2))/TMath::Power(Fxtime[i],2); 
        std::cout << "Sigma=" << Sigma[i] << " +- " << eSigma[i] << std::endl; 
        std::cout << "Sigma=" << Sigma[i] << " +- " << eSigma2[i] << std::endl; 

        SigmaPixel[i] = Sigma[i]/AllPixel;
        eSigmaPixel[i] = eSigma[i]/AllPixel;
        eSigmaPixel2[i] = eSigma2[i]/AllPixel;
        std::cout << "SigmaPixel=" << SigmaPixel[i] << " +- " << eSigmaPixel[i] << std::endl; 
        std::cout << "SigmaPixel=" << SigmaPixel[i] << " +- " << eSigmaPixel2[i] << std::endl; 

        allN += N[i];
        allFxtime += Fxtime[i];
    }
        std::cout << "**************************************************" << std::endl; 

    double alleFxtime;

    //all cross section with N error
    alleN = sqrt(allN);
    std::cout << "allN=" << allN << " +- " << alleN << std::endl; 
    std::cout << "allFxtime=" << allFxtime << " +- " << std::endl; 
    allSigma = allN/allFxtime;
    alleSigma = alleN/allFxtime;
    allSigmaPixel = allSigma/AllPixel;
    alleSigmaPixel = alleSigma/AllPixel;
    std::cout << "allSigmaPixel=" << allSigmaPixel << " +- " << alleSigmaPixel << std::endl; 

    //all cross section with beam error
    alleFxtime = (1/(TMath::Power(Fxtime[0]+Fxtime[1]+Fxtime[2]+Fxtime[3],2)))*sqrt(eFxtime[0]*eFxtime[0]+eFxtime[1]*eFxtime[1]+eFxtime[2]*eFxtime[2]+eFxtime[3]*eFxtime[3]);
    alleSigmaPixel2 = allN*alleFxtime/AllPixel;
    std::cout << "allSigmaPixel=" << allSigmaPixel << " +- " << alleSigmaPixel2 << std::endl; 


    return;
}


