//for calculation of the beam point 
#include "TF1.h"
#include "TMinuit.h"
#include <iostream>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

static const double ECHARGE = 1.6*1.0e-19;
static const double Current = 1.23*1.0e-9; //[A]
static const double Time = 240-2*18; //[s]
static const double beamsigmax =3.73 ; //[mm]
static const double beamsigmay =4.99 ; //[mm]
static const double samplesizex=20.; //[mm]
static const double samplesizey=9.6; //[mm]

static const int nbinx = 400;
static const int nbiny = 192;
//static const double nlatch = (8/25)*3+(17/25)*8; //6.4
static const double nlatch = 6.4;

double b[nbinx+1][nbiny+1];
double m[nbinx+1][nbiny+1];

void loglikelihood(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag){
    double y = 0;
    for(int i=1; i<=400; i++){
        for(int j=1; j<=192; j++){
            double yi = 0;
            yi = -m[i][j]*log(b[i][j]*par[0])+b[i][j]*par[0];
            y += yi;
        }
    }
    f = y;
}

void forfit(){

    /////////////////////////////////////////////////////////////////////
    string finname = "/Users/fujimoto/cyric11/cyricAnalysis/macros/results/outputplace_run00053.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    TH2F *h2 = (TH2F*)fin->Get("h2"); 
    /////////////////////////////////////////////////////////////////////

    double S = (samplesizex/nbinx)*(samplesizey/nbiny)*0.01; //[cm]*[cm]
    std::cout << "S= "<< S << std::endl;
    
    double A = nlatch*Time*Current/ECHARGE/S;
    std::cout << "A= "<< A << std::endl;

    TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",0,20,0,10); 
    double coefficient = 1/(2*M_PI*beamsigmax*beamsigmay);
    f2->SetParameters(coefficient,samplesizex/2.,beamsigmax,samplesizey/2.,beamsigmay); 

    double xmin = 0;
    double xmax = samplesizex;
    double ymin = 0;
    double ymax = samplesizey;
    TH2D *h1=new TH2D("h1","beamspot",nbinx,xmin,xmax,nbiny,ymin,ymax);
    double y = 0;
    for(int ix = 1;ix<=nbinx;ix++){
        for(int iy = 1;iy<=nbiny;iy++){
            double val = h1->GetBinContent(ix,iy);
            h1->SetBinContent(ix,iy,val+f2->Eval(h1->GetXaxis()->GetBinCenter(ix),h1->GetYaxis()->GetBinCenter(iy)));
            /*
            b[ix][iy] = h1->GetBinContent(ix,iy);
            m[ix][iy] = h2->GetBinContent(ix,iy);
            std::cout << "b["<< ix << "][" << iy << "]= " << b[ix][iy] << std::endl;
            std::cout << "m["<< ix << "][" << iy << "]= " << m[ix][iy] << std::endl;
            */
        }
    }
    double integral = h1->Integral();
    std::cout << "integral= "<< integral << std::endl;
    h1->Scale(1./h1->Integral());
    integral = h1->Integral();
    std::cout << "integral= "<< integral << std::endl;
    //double mean = h1->GetMaximum();
    //std::cout << "max1= "<< mean << std::endl;
    h1->Scale(A);
    integral = h1->Integral();
    std::cout << "integral= "<< integral << std::endl;

    for(int ix = 1;ix<=nbinx;ix++){
        for(int iy = 1;iy<=nbiny;iy++){
            b[ix][iy] = h1->GetBinContent(ix,iy);
            m[ix][iy] = h2->GetBinContent(ix,iy);
            //std::cout << "b["<< ix << "][" << iy << "]= " << b[ix][iy] << std::endl;
            //std::cout << "m["<< ix << "][" << iy << "]= " << m[ix][iy] << std::endl;
        }
    }

    //use TMinuit 
    TMinuit *min = new TMinuit(1);
    min->SetPrintLevel(1);
    min->SetFCN(loglikelihood);
    int ierflg = 0;

    double par, parErr;
    string parName = "para";
    double stepSize = 1.0e-15, minVal = 1.0e-15, maxVal = 1.0e-13;
    par = 2.8e-14;

    min->DefineParameter(0, parName.c_str(), par, stepSize, minVal, maxVal);
    int migrad_stats = min->Migrad();

    min->GetParameter(0, par, parErr);
    std::cout << "************************************************" << std::endl;
    std::cout << "Result: " <<par << " +/- " << parErr << std::endl;
    std::cout << "Status of Migrad: " << migrad_stats << std::endl;

    delete min;

    TCanvas *c1 = new TCanvas("c1","c1",800,400);
    h1->SetXTitle("x (mm)");
    h1->SetYTitle("y (mm)");
    h1->SetStats(0);
    //gStyle->SetPalette(1);
    h1->Draw("colz");

    std::cout << "# of bitflip=  " << h2->GetEntries() << std::endl;

    return;
}

