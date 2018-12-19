#include "TF2.h"
#include "TH2.h"
#include "TMath.h"

Double_t g2(Double_t *x, Double_t *par) {
    Double_t r1 = Double_t((x[0]-par[1])/par[2]);
    Double_t r2 = Double_t((x[1]-par[3])/par[4]);
    return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}
Double_t fun2(Double_t *x, Double_t *par) {
    Double_t *p1 = &par[0];
    Double_t result = g2(x,p1);
    return result;
}

void beamfit() {
    const Int_t npar = 5;
    Double_t f2params[npar] = {1,0,4.5,0,4}; //set parameter (mean and beam sigma)
    TF2 *f2 = new TF2("f2",fun2,-10,10,-5,5, npar);
    f2->SetParameters(f2params);

    /////////////////////////////////////////////////////////////
    string finname = "/Users/fujimoto/cyric11/cyricAnalysis/macros/results/outputplace_run00044.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    TH2F *h2 = (TH2F*)fin->Get("h2"); 
    /////////////////////////////////////////////////////////////
    h2->RebinX(8);
    h2->RebinY(8);
    h2->Draw("colz");
    
    //Create an histogram and fill it randomly with f2
    //TH2F *h2 = new TH2F("h2","beam",50,-10,10,48,-5,5);
    //Int_t nentries = 7110;
    //h2->FillRandom("f2",nentries);
    //h2->Draw("colz");

    //Fit h2 with f2
    //Float_t ratio = 4*nentries/9480;
    //f2params[0] *= ratio;
    //f2->SetParameters(f2params);
    
    h2->Fit("f2");
    f2->Draw("cont1 same");
    
    return;
    double total = h2->Integral();
    h2->Scale(1./total);

    //get the ratio
    float z[h2->GetNbinsX()+1][h2->GetNbinsY()+1];
    float z2[h2->GetNbinsX()+1][h2->GetNbinsY()+1];
    for (int i=1; i<h2->GetNbinsX()+1; i++){
        for (int j=1; j<h2->GetNbinsY()+1; j++){
            z[i][j] = h2->GetBinContent(h2->GetBin(i,j))*1.0e14;
            z2[i][j] = h2->GetBinContent(h2->GetBin(i,j))*1.0e14+5.0e15;
        }
    }
}

