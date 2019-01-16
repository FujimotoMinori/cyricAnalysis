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
    string finname = "/Users/fujimoto/cyric11/cyricAnalysis/macros/results/outputplace_run00046.root";

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
    h2->SetTitle("flipped pixel register");
    h2->SetTitleSize(0.12);
    h2->SetXTitle("col");
    h2->SetYTitle("row");
    h2->GetXaxis()->SetTitleOffset(0.8);
    h2->GetYaxis()->SetTitleOffset(0.8);
    h2->GetXaxis()->SetTitleSize(0.05);
    h2->GetYaxis()->SetTitleSize(0.05);
    TH1D *pjx = h2->ProjectionX("ProjectionX",0,192);
    TH1D *pjy = h2->ProjectionY("ProjectionY",0,400);

    //fit histogram
    TF1 *fx = new TF1("fx","gaus",0,400);
    TF1 *fy = new TF1("fy","gaus",0,400);

    //fx->SetParameter(0,180);
    fx->SetParameter(1,200);
    fy->SetParameter(1,90);

    pjx->SetStats(0);
    pjy->SetStats(0);
    TCanvas *c2 = new TCanvas("c2", "c2");
    pjx->Draw();
    pjx->Fit("fx","l","",0,400);
    double meanx = fx->GetParameter(1);
    double emeanx = fx->GetParError(1);
    double sigmax = fx->GetParameter(2);
    double esigmax = fx->GetParError(2);
    std::cout << "mean=" << meanx << std::endl;
    std::cout << "sigma=" << sigmax << std::endl;
    std::cout << "esigma=" << esigmax << std::endl;
    std::cout << "beamsigma=" << sigmax*50e-6*1000 << " mm" << std::endl;
    std::cout << "ebeamsigma=" << esigmax*50e-6*1000 << " mm" << std::endl;

    TCanvas *c3 = new TCanvas("c3", "c3");
    pjy->Draw();
    pjy->Fit("fy","l","",0,192);
    double meany = fy->GetParameter(1);
    double emeany = fy->GetParError(1);
    double sigmay = fy->GetParameter(2);
    double esigmay = fy->GetParError(2);
    std::cout << "mean=" << meany << std::endl;
    std::cout << "sigma=" << sigmay << std::endl;
    std::cout << "esigma=" << esigmay << std::endl;
    std::cout << "beamsigma=" << sigmay*50e-6*1000 << " mm" << std::endl;
    std::cout << "ebeamsigma=" << esigmay*50e-6*1000 << " mm" << std::endl;

    const Int_t npar = 5;
    Double_t f2params[npar] = {1,0,3,0,3};
    TF2 *f2 = new TF2("f2",fun2,-10,10,-5,5, npar);
    f2->SetParameters(f2params);

    //Create an histogram and fill it randomly with f2
    TH2F *h2org = new TH2F("h2org","beam",50,-10,10,48,-5,5);
    Int_t nentries = h2->GetEntries();
    std::cout << "nentries=" << nentries << std::endl;
    //h2org->Fill(h2->GetBinContent());

    return;

    h2org->FillRandom("f2",nentries);
    h2org->Draw("colz");

    //Fit h2 with f2
    //Float_t ratio = 4*nentries/9480;
    //f2params[0] *= ratio;
    //f2->SetParameters(f2params);
    h2org->Fit("f2");
    f2->Draw("cont1 same");

}

