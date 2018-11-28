#include "TF2.h"
#include "TH2.h"
#include "TMath.h"

Double_t g2(Double_t *x, Double_t *par) {
    Double_t r1 = Double_t((x[0]-par[1])/par[2]);
    Double_t r2 = Double_t((x[1]-par[3])/par[4]);
    return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2))*5.6e12/*+5.0e15*/;
}
Double_t fun2(Double_t *x, Double_t *par) {
    Double_t *p1 = &par[0];
    Double_t result = g2(x,p1);
    return result;
}

void calcflux() {
    const Int_t npar = 5;
    Double_t f2params[npar] = {1,0,3,0,3};
    TF2 *f2 = new TF2("f2",fun2,-10,10,-10,10, npar);
    f2->SetParameters(f2params);

    //Create an histogram and fill it randomly with f2
    TH2F *h2 = new TH2F("h2","beam",50,-10,10,48,-5,5);
    long long nentries = 1.0e14;
    h2->FillRandom("f2",nentries);
    h2->Draw("colz");

    //double total = h2->Integral();
    //h2->Scale(1./total);

    //get the ratio
    //TH2F *h3 = new TH2F("h3","beamraio",50,-10,10,48,-5,5);
    float z[h2->GetNbinsX()+1][h2->GetNbinsY()+1];
    double rat = 0.;
    for (int i=1; i<h2->GetNbinsX()+1; i++){
        for (int j=1; j<h2->GetNbinsY()+1; j++){
            z[i][j] = h2->GetBinContent(h2->GetBin(i,j));
            //std::cout << "z[" << i  << "][" << j << "]= " << z[i][j] << std::endl; 
        }
    }

    std::cout << "z= "<< z[50][48] << std::endl;
    double max = h2->GetBinContent(h2->GetMaximumBin());
    std::cout << "max= "<< max << std::endl;
    double min = h2->GetBinContent(h2->GetMinimumBin());
    double minbin = h2->GetMinimumBin();
    std::cout << "min= "<< min << std::endl;
    std::cout << "minbin= "<< minbin << std::endl;
    rat = max/min;
    std::cout <<  "rat=  " << rat << std::endl;
    //h3->Draw("colz");

}

