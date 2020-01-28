/*
 add3Hist.cxx
 just compare histograms of 3 runs 
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

void add3Hist(){
  string finname1 = "output47.root"; //run47
  string finname2 = "output51.root"; //run51
  string finname3 = "output52.root"; //run52

  //open files
  TFile* fin1 = TFile::Open(finname1.c_str(), "READ");
  TFile* fin2 = TFile::Open(finname2.c_str(), "READ");
  TFile* fin3 = TFile::Open(finname2.c_str(), "READ");
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

  if (!fin3) {
    cout << " input file:" << finname3.c_str() << " does not exist"<< endl;
    return ;
  }
  cout << " input file:" << finname3.c_str() << " open..." << endl;

  //get histograms
  TH1F *htot1 = (TH1F*)fin1->Get("htot");
  TH1F *htot2 = (TH1F*)fin2->Get("htot");
  TH1F *htot3 = (TH1F*)fin3->Get("htot");
  cout << "----- got 3 hist -----" << endl;

  TCanvas *c1 = new TCanvas("c1", "c1");
  htot1->SetLineColor(kRed);
  htot1->Draw();
  htot2->SetLineColor(kBlue);
  htot2->Draw("same");
  htot3->SetLineColor(kBlack);
  htot3->Draw("same");
  c1->SaveAs("htot.pdf");
  //TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
  //leg->AddEntry(heff1,"357050","f");
  //leg->AddEntry(heff2,"354107","f");
  //leg->Draw();

}

