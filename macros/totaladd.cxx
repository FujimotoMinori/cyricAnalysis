/*
    totaladd.C
    total number of flip bit
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TString.h>

int totaladd(const string& inputFile){
  std::cout << "#-----start totaladd.cxx-----" << std::endl;
 
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
 
  //make hitogram
  TH2F* hcol = new TH2F("h2","flipped col in each address",138,0,137,192,0,192);
  TH2F* hrow = new TH2F("h2","flipped row in each address",138,0,137,400,0,400);
  //TH1F *hcol = new TH1F("flipped column","",192,0,192);
  //TH1F *hrow = new TH1F("flipped row","",400,0,400);
  //TH2F *haddr = new TH2F("flipped addr",0,192,192,0,400,400);

  //read file
  char a[1000] = {};
  int b;
  int c;
  int d;
  int count = 0;
  int totalval[1000] = {};
  //int columnn[500][1000] ;
  //int row[500][1000];
  while(getline(fin,str))
  {
    if(str[0] == '#') continue;
    if(str[0] == 't'){
      b = 0;
      sscanf(str.data(),"%s %d",a,&b);
      ++count;
      totalval[count] = b;
    }else{
      sscanf(str.data(),"%d %d",&c,&d);
      //row[count] = c;
      //column[count] = d;
      //std::cout << "count= " << count << ",flipped row= " << c << std::endl;
      hrow->Fill(count,c);
      hcol->Fill(count,d);
    }
  }
  std::cout << "#count=" << count << std::endl;
  std::cout << "#rowcount= "  << std::endl;

  //set root file for output
  string foutname = "outputAddr.root";
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

  //hcol->Draw("colz");
  hrow->Draw("colz");

  fout->Write();
  fout->Close();

  fin.close();

  return 0;
  std::cout << "#-----finished totaladd.cxx-----" << std::endl;

}

