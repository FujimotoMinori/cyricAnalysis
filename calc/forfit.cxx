//for calculation of the beam point 
#include "TF1.h"
#include "TMinuit.h"
#include <iostream>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

static const double ECHARGE = 1.6*1.0e-19;
static const double Current = 0.99*1.0e-9; //[A]
static const double Time = 388; //[s]

double b[401][193];
double m[401][193];

void loglikelihood(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag){
    double y = 0;
    for(int i=1; i<=400; i++){
        for(int j=1; j<=192; j++){
            double yi = 0;
            //std::cout << "b["<< i << "][" << j << "]= " << b[i][j] << std::endl;
            //std::cout << "m["<< i << "][" << j << "]= " << m[i][j] << std::endl;
            yi = -m[i][j]*log(b[i][j]*par[0])+b[i][j]*par[0];
            y += yi;
        }
    }
    f = y;
}

void forfit(){

    /////////////////////////////////////////////////////////////////////
    string finname = "/Users/fujimoto/cyric11/cyricAnalysis/macros/results/outputplace_run00046.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    TH2F *h2 = (TH2F*)fin->Get("h2"); 
    /////////////////////////////////////////////////////////////////////

    double beamsigmax =4. ; //[mm]
    double beamsigmay =4. ; //[mm]
    double samplesizex=20.; //[mm]
    double samplesizey=10.; //[mm]

    int nbinx = 400;
    int nbiny = 192;
    int nlatch = 1;
    double S = (samplesizex/nbinx)*(samplesizey/nbiny)*0.01; //[cm]*[cm]
    std::cout << "S= "<< S << std::endl;
    
    double A = nlatch*Time*Current/ECHARGE/S;
    std::cout << "A= "<< A << std::endl;

    //double b[nbinx+1][nbiny+1];
    //double m[nbinx+1][nbiny+1];

    TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",0,20,0,10); 
    f2->SetParameters(A,samplesizex/2.,beamsigmax,samplesizey/2.,beamsigmay); 

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
            b[ix][iy] = h1->GetBinContent(ix,iy);
            m[ix][iy] = h2->GetBinContent(ix,iy);
        }
    }

    //use TMinuit 
    TMinuit *min = new TMinuit(1);
    min->SetPrintLevel(1);
    min->SetFCN(loglikelihood);
    int ierflg = 0;

    double par, parErr;
    string parName = "para";
    double stepSize = 1, minVal = 0., maxVal = 0.;

    min->DefineParameter(0, parName.c_str(), par, stepSize, minVal, maxVal);
    int migrad_stats = min->Migrad();

    min->GetParameter(0, par, parErr);
    std::cout << "************************************************" << std::endl;
    std::cout << "Result: " <<par << " +/- " << parErr << std::endl;
    std::cout << "Status of Migrad: " << migrad_stats << std::endl;

    delete min;

    TCanvas *c1 = new TCanvas("c1","c1");
    h2->SetStats(0);
    h2->Draw("colz");

    return;
}

