//for calculation of the beam point 
#include "TF1.h"

void forfit(){

    /////////////////////////////////////////////////////////////
    string finname = "/Users/fujimoto/cyric11/cyricAnalysis/macros/results/outputplace_run00044.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    TH2F *h2 = (TH2F*)fin->Get("h2"); 
    /////////////////////////////////////////////////////////////

    float sigma;
    int nlatch = 8;

    double beamsigmax =4. ;
    double beamsigmay =4. ;
    double samplesizex=20.;
    double samplesizey=10.;

    TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",0,20,0,10); 
    f2->SetParameters(1,samplesizex/2.,beamsigmax,samplesizey/2.,beamsigmay); 

    int nbinx = 400;
    int nbiny = 192;
    double S = (samplesizex/nbinx)*(samplesizey/nbiny);
    std::cout << S << std::endl;
    double b[nbinx+1][nbiny+1];
    double b2[nbinx+1][nbiny+1];

    double xmin = 0;
    double xmax = samplesizex;
    double ymin = 0;
    double ymax = samplesizey;

    TH2D *h1=new TH2D("h1","beamspot",nbinx,xmin,xmax,nbiny,ymin,ymax);
    for(int ix = 1;ix<=nbinx;ix++){
        for(int iy = 1;iy<=nbiny;iy++){
            double val = h1->GetBinContent(ix,iy);
            h1->SetBinContent(ix,iy,val+f2->Eval(h1->GetXaxis()->GetBinCenter(ix),h1->GetYaxis()->GetBinCenter(iy)));
            b[ix][iy] = h1->GetBinContent(ix,iy)/**sigma*8/nlatch*/;
            b2[ix][iy] = h2->GetBinContent(ix,iy);
        }
    }

    //TCanvas *c1 = new TCanvas("c1","c1");
    //h1->SetStats(0);
    //h1->Draw("colz");

    return;
}

