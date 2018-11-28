#include "TF2.h"
#include "TH2.h"
#include "TMath.h"

// Fitting a 2-D histogram
// This tutorial illustrates :
//  - how to create a 2-d function
//  - fill a 2-d histogram randomly from this function
//  - fit the histogram
//  - display the fitted function on top of the histogram
//
// This example can be executed via the interpreter or ACLIC
//   root > .x fit2.C
//   root > .x fit2.C++
//Author: Rene Brun

Double_t g2(Double_t *x, Double_t *par) {
    Double_t r1 = Double_t((x[0]-par[1])/par[2]);
    Double_t r2 = Double_t((x[1]-par[3])/par[4]);
    return 1.0e12*par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2))/*+5.0e15*/;
}
Double_t fun2(Double_t *x, Double_t *par) {
    Double_t *p1 = &par[0];
    Double_t *p2 = &par[5];
    Double_t *p3 = &par[10];
    Double_t result = g2(x,p1) /*+ g2(x,p2) + g2(x,p3)*/;
    return result;
}

void fit2() {
    const Int_t npar = 15;
    Double_t f2params[npar] =
    {1,0,3,0,3,160,0,0.8,0,0.9,40,4,0.7,4,0.7};
    TF2 *f2 = new TF2("f2",fun2,-10,10,-10,10, npar);
    f2->SetParameters(f2params);

    //Create an histogram and fill it randomly with f2
    TH2F *h2 = new TH2F("h2","beam",200,-10,10,100,-5,5);
    Int_t nentries = 100000;
    h2->FillRandom("f2",nentries);
    h2->Draw("colz");

    //get the ratio
    TH2F *h3 = new TH2F("h3","beamraio",50,-10,10,48,-5,5);
    double z[h2->GetNbinsX()+1][h2->GetNbinsY()+1];
    for (int i=1; i<h2->GetNbinsX()+1; i++){
        for (int j=0; j<h2->GetNbinsY()+1; j++){
            z[i][j] = h2->GetBinContent(h2->GetBin(i,j));
            if(z[i][j] !=0 ) std::cout << z[i][j] << std::endl;
            //h3->Fill(z[i][j]);
        }
    }
    //h3->Draw("colz");

    //Fit h2 with original function f2
    Float_t ratio = 4*nentries/100000;
    f2params[ 0] *= ratio;
    //f2params[ 5] *= ratio;
    //f2params[10] *= ratio;
    f2->SetParameters(f2params);
    h2->Fit("f2");
    f2->Draw("cont1 same");
}

