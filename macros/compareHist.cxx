/*
 compareHist.cxx
 just compare graphs of GR and PR
*/

#include <iostream>
#include <sstream>
#include <TFile.h>
#include <TH1.h>
#include <TH2D.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TString.h>
using namespace std;

void compareHist(){
  string finname1 = "/afs/cern.ch/work/m/mfujimot/public/timing/PixelTiming/TimingScanAna/macros/makePlot/histIBL357050_noToTcut.root"; //August
  string finname2 = "/afs/cern.ch/work/m/mfujimot/public/timing/PixelTiming/TimingScanAna/macros/makePlot/hist.root"; //June

  //open files
  TFile* fin1 = TFile::Open(finname1.c_str(), "READ");
  TFile* fin2 = TFile::Open(finname2.c_str(), "READ");
  if (!fin1) {
    cout << " input file:" << finname1.c_str() << " does not exist"<< endl;
    return ;
  }
  cout << " input file:" << finname1.c_str() << " open..." << endl;

  if (!fin2) {
    cout << " input file:" << finname2.c_str() << " does not exist"<< endl;
    return ;
  }
  cout << " input file:" << finname2.c_str() << " open..." << endl;

  //get histograms
  TH1F *heff1 = (TH1F*)fin1->Get("effIBL");
  TH1F *heff2 = (TH1F*)fin2->Get("effIBL");
  TH1F *hdel1 = (TH1F*)fin1->Get("RelDelayIBL");
  TH1F *hdel2 = (TH1F*)fin2->Get("RelDelayIBL");
  TH1F *hdiff1 = (TH1F*)fin1->Get("diffIBL");
  TH1F *hdiff2 = (TH1F*)fin2->Get("diffIBL");
  cout << "----- got hist -----" << endl;

  TCanvas *c1 = new TCanvas("c1", "c1");
  heff1->SetLineColor(kRed);
  heff1->Draw();
  heff2->SetLineColor(kBlue);
  heff2->Draw("same");
  c1->SaveAs("heff.png");
  //TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
  //leg->AddEntry(heff1,"357050","f");
  //leg->AddEntry(heff2,"354107","f");
  //leg->Draw();
/*   
  TCanvas *c2 = new TCanvas("c2", "c2");
  hdel1->SetLineColor(kRed);
  hdel1->Draw();
  hdel2->SetLineColor(kBlue);
  hdel2->Draw("same");

  TCanvas *c3 = new TCanvas("c3", "c3");
  hdiff1->SetLineColor(kRed);
  hdiff1->Draw();
  hdiff2->SetLineColor(kBlue);
  hdiff2->Draw("same");
  //c3->SaveAs("hdiff.png");
  //*/
}

