//for calculation of the beam point 
#include "TF1.h"
#include "TMinuit.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#define _USE_MATH_DEFINES
using namespace std;

//run44
static const double ECHARGE = 1.6*1.0e-19;
static const double Current = 1.01*1.0e-9; //[A]
static const double eCurrent = 0.09*1.0e-9; //[A]
static const double Time = 180-2*18; //[s]
static const double beamsigmax =3.88 ; //[mm]
static const double ebeamsigmax =0.05 ; //[mm]
static const double beamsigmay =5.24 ; //[mm]
static const double ebeamsigmay =0.35 ; //[mm]
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

void forfiterr(){

    /////////////////////////////////////////////////////////////////////
    string finname = "/Users/fujimoto/cyric11/cyricAnalysis/macros/results/outputplace_run00044.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    TH2F *h2 = (TH2F*)fin->Get("h2"); 
    /////////////////////////////////////////////////////////////////////
    //set textfile for summary output
    std::ofstream summary("crosssections.txt" /*,std::ios::app*/);

    std::cout << "curret= "<< Current<< std::endl;
    std::cout << "x= "<< beamsigmax<< std::endl;
    std::cout << "y= "<< beamsigmay<< std::endl;
    std::vector<double> eC={Current+eCurrent, Current-eCurrent};     
    std::vector<double> ebx={beamsigmax+ebeamsigmax, beamsigmax-ebeamsigmax};     
    std::vector<double> eby={beamsigmay+ebeamsigmay, beamsigmay-ebeamsigmay};     

    double S = (samplesizex/nbinx)*(samplesizey/nbiny)*0.01; //[cm]*[cm]
    std::cout << "S= "<< S << std::endl;


    for(int i=0;i<eC.size();++i){
        for(int j=0;j<ebx.size();++j){
            for(int k=0;k<eby.size();++k){
                std::cout << "eC= "<< eC[i] << std::endl;
                std::cout << "ebx= "<< ebx[j] << std::endl;
                std::cout << "eby= "<< eby[k] << std::endl;
                summary << "eC= "<< eC[i] << std::endl;
                summary << "ebx= "<< ebx[j] << std::endl;
                summary << "eby= "<< eby[k] << std::endl;

                double A = nlatch*Time*eC[i]/ECHARGE/S;
                std::cout << "A= "<< A << std::endl;

                TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",0,20,0,10); 
                double coefficient = 1/(2*M_PI*ebx[j]*eby[k]);
                f2->SetParameters(coefficient,samplesizex/2.,ebx[j],samplesizey/2.,eby[k]); 

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
                    }
                }
                double integral = h1->Integral();
                std::cout << "integral= "<< integral << std::endl;
                h1->Scale(1./h1->Integral());
                integral = h1->Integral();
                std::cout << "integral= "<< integral << std::endl;
                h1->Scale(A);
                integral = h1->Integral();
                std::cout << "integral= "<< integral << std::endl;

                for(int ix = 1;ix<=nbinx;ix++){
                    for(int iy = 1;iy<=nbiny;iy++){
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
                double stepSize = 1.0e-15, minVal = 1.0e-15, maxVal = 1.0e-13;
                par = 2.8e-14;

                min->DefineParameter(0, parName.c_str(), par, stepSize, minVal, maxVal);
                int migrad_stats = min->Migrad();

                min->GetParameter(0, par, parErr);
                std::cout << "************************************************" << std::endl;
                std::cout << "Result: " <<par << " +/- " << parErr << std::endl;
                summary << "Result: " <<par << " +/- " << parErr << std::endl;
                std::cout << "Status of Migrad: " << migrad_stats << std::endl;

                h1->Clear();
                delete min;

                /*
                   TCanvas *c1 = new TCanvas("c1","c1");
                   h1->SetXTitle("x (mm)");
                   h1->SetYTitle("y (mm)");
                   h1->SetStats(0);
                   h1->Draw("colz");
                   std::cout << "# of bitflip=  " << h2->GetEntries() << std::endl;
                 */

            }
        }
    }

    summary.close();
    return;
}

