/*
    total.C
    read summary file (summary*.txt) and just make graph of primary function
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

int total(const string& inputFile){
  std::cout << "#-----start total.cxx-----" << std::endl;
 
  //set open file
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
  string foutname = "outputPR.root";
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

  /*
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
  */
  
  //draw graph
  TCanvas *c1 = new TCanvas("c", "c",1000,1000);
  TGraph *grt = new TGraph(count);
  for(int j=1;j<count+1;++j){
    if(totalval[j] > 20000) continue; 
    grt->SetPoint(j,j,totalval[j]);
  }

  grt->SetTitle("SEU test;Readout Cycle;number of flip bit");
  grt->SetMarkerStyle(20);
  grt->SetMarkerColor(kBlue);
  grt->SetMarkerSize(1.0);
  grt->SetMaximum(30000);
  grt->GetXaxis()->SetLimits(0,145);
  grt->Draw("AP");

  //fitting 
  //TF1 * f1 = new TF1("func","pol1",20,100);
  TF1 *f = new TF1("f","[0]+[1]*x",20,20);
  //grt->Fit("func");
  grt->Fit(f,"","",10,130);
  double p0 = 0.;
  double p1 = 0.;
  double n = 0.;
  p0 = f->GetParameter(0);
  p1 = f->GetParameter(1);

  std::cout << "p0= " << p0 << std::endl; 
  std::cout << "p1= " << p1 << std::endl; 

  n =  p0+p1*(-1*(p0/p1)+132);
  std::cout << "n= " << n << std::endl; 

  grt->Write();

  c1->Write();
  fout->Write();
  fout->Close();

  fin.close();

  return 0;
  std::cout << "#-----finished total.cxx-----" << std::endl;

}


