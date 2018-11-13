/*
    totalGR_org.C
    total number of flip address
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2D.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TString.h>

int totalGR_org(const string& inputFile){
  std::cout << "#-----start totalGR_org.cxx-----" << std::endl;
 
  //set open file
  //TString ifn = "summary.txt";
  TString ifn = inputFile;
  ifstream fin;
  std::string str;

  //open files
  fin.open(ifn);
  if(fin.fail()){
    cerr << "#cannot open file1 : " << ifn << std::endl;
    return 1;
  }

  std::cout << "#finished opening files" << std::endl;

  //read file
  char a[10000] = {};
  int b;
  int c;
  int count = 0;
  int bcount = 0;
  int totalval[10000] = {};
  int btotalval[8][10000] = {};
  while(getline(fin,str))
  {
    if(str[0] == '#') continue;
    if(str[0] == 't') {
      b = 0;
      sscanf(str.data(),"%s %d",a,&b);
      ++count;
      bcount = 0;
      totalval[count] = b;
    }else{
      c = 0;
      sscanf(str.data(),"%d",&c);
      ++bcount;
      btotalval[bcount-1][count+1] = c;
    }
  }

  std::cout << "#count=" << count << std::endl;

  //set root file for output
  string foutname = "outputbitGR_org.root";
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

  //sum
  for(int i=1;i<count+1;i++){
    //std::cout << "count=" << i << std::endl;
    totalval[i] += totalval[i-1];
    for(b=0;b<8;b++){
      btotalval[b][i] += btotalval[b][i-1];
      //std::cout << "btotalval["<< i  << "]= "<< btotalval[b][i] << std::endl;
    }
    //std::cout << "totalval["<< i  << "]= "<< totalval[i] << std::endl;
  }
  

  //draw graph
  TCanvas *c1 = new TCanvas("c", "c",1000,1000);
  TGraph *grt = new TGraph(count);
  for(int j=1;j<count+1;++j){
    grt->SetPoint(j,j,totalval[j]);
  }
  grt->SetMarkerStyle(20);
  grt->SetMarkerColor(kBlue);
  grt->SetMarkerSize(1.0);
  grt->Draw("AP");

  /*
  TCanvas *c1 = new TCanvas("c", "c",1000,1000);
  gStyle->SetOptStat(11);
  c1->Divide(2,4);
  c1->cd(1); 
  h0->Draw("colz");
*/
 
  c1->Write();
  fout->Write();
  fout->Close();

  fin.close();

  return 0;
  std::cout << "#-----finished totalGR_org.cxx-----" << std::endl;

}




