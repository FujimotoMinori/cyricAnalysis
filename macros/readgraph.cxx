/*
    readgraph.C
    read graph and fit by primary function
*/
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2D.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TString.h>


int readgraph(/*const string& inputFile*/){
  std::cout << "#-----start readgraph.cxx-----" << std::endl;
 
  //set open file
  //TString ifn = inputFile;
  string finname = "/home/pixeldaq/cyric/afterIrrad/src/registerresults/summaryoutput_run00030.root";

  //file open
  TFile* fin = TFile::Open(finname.c_str(), "READ");
  if (!fin) {
      cout << " input file:" << finname.c_str() << " does not exist"<< endl;
      return 0;
  }
  cout << " input data file:" << finname.c_str() << " open..." << endl;

  //get graph
  TGraph *tgraph = (TGraph*)fin->Get("graph"); 

  //set root file for output
  string foutname = "newGraph.root";
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");
  
  //fitting 
  TF1 * f1 = new TF1("func","pol1",40,90);

  //draw graph
  tgraph->SetTitle("new graph");
  tgraph->SetMaximum(20e3);
  tgraph->Fit("func");
  tgraph->Draw("AP");
  tgraph->Write();
 
  fout->Write();
  fout->Close();

  return 0;
  std::cout << "#-----finished readgraph.cxx-----" << std::endl;

}

