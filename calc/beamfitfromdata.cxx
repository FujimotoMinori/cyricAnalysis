/*
    beamfitfromdata.cxx
    read histogram and fit by 2Dgaussian
*/
#include "TF2.h"
#include "TH2.h"
#include "TH1D.h"
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

void beamfitfromdata(/*const string& inputFile*/) {
    std::cout << "#-----start beamfitfromdata.cxx-----" << std::endl;

    //string finname = inputFile;
    string finname = "/Users/fujimoto/cyric11/cyricData/summaryrowcol_run00052.root";

    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    if (!fin) {
        cout << " input file:" << finname.c_str() << " does not exist"<< endl;
        return;
    }
    cout << " input data file:" << finname.c_str() << " open..." << endl;

    //get histogram
    TH2F *h2 = (TH2F*)fin->Get("h2"); 
    //draw histogram
    TCanvas *c1 = new TCanvas("c1", "c1");
    h2->Draw("colz");
    //Int_t first = h2->GetXaxis()->FindBin(0.);
    //Int_t last  = h2->GetXaxis()->FindBin(192.);
    TH1D *pjx = h2->ProjectionX("ProjectionX",0,192);
    TH1D *pjy = h2->ProjectionY("ProjectionY",0,400);
    pjx->SetStats(0);
    pjy->SetStats(0);
    TCanvas *c2 = new TCanvas("c2", "c2");
    pjx->Draw();
    TCanvas *c3 = new TCanvas("c3", "c3");
    pjy->Draw();

    return;

    const Int_t npar = 5;
    Double_t f2params[npar] = {1,0,3,0,3};
    TF2 *f2 = new TF2("f2",fun2,-10,10,-5,5, npar);
    f2->SetParameters(f2params);

    //Create an histogram and fill it randomly with f2
    TH2F *h2org = new TH2F("h2org","beam",50,-10,10,48,-5,5);
    Int_t nentries = h2->GetEntries();
    std::cout << "nentries=" << nentries;

    h2org->FillRandom("f2",nentries);
    h2org->Draw("colz");

    //Fit h2 with f2
    //Float_t ratio = 4*nentries/9480;
    //f2params[0] *= ratio;
    //f2->SetParameters(f2params);
    h2org->Fit("f2");
    f2->Draw("cont1 same");
    
    double total = h2org->Integral();
    h2org->Scale(1./total);

}


