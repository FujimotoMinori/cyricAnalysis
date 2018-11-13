/*
    totalGR.C
    analyze summaryGR.txt
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

void totalGR(const string& inputFile){
  std::cout << "#-----start totalGR.cxx-----" << std::endl;
 
  //set file
  TString ifn = inputFile;
  ifstream fin;
  std::string str;

  //open files
  fin.open(ifn);
  if(fin.fail()){
    cerr << "#cannot open file1 : " << ifn << std::endl;
    return;
  }
  std::cout << "#finished opening files" << std::endl;

  //make histogram
  TH2F* h2 = new TH2F("h2","flipped bit;count;flipped address of GR",151,0,150,138,0,137);

  //read file
  const int n_Address = 138;
  int a,b,c;
  char s;
  int add[1000] = {};
  int val1[1000][n_Address] = {};
  int val2[1000][n_Address] = {};
  int tn[100000] = {};
o int count = 0;
  int nflip = 0;

  while(getline(fin,str))
  {
    if(str[0] == '#') continue;
    else if(str[0] == 'v') continue;
    else if(str[0] == 't'){
      sscanf(str.data(), "%s %d", &s, &b);
      ++count;
      nflip = 0;
      tn[count] = b;
      std::cout << "-------------------------------total bit flipped in count " << count << "= " << tn[count] << std::endl;
    } else {
      a = 0; 
      b = 0; 
      sscanf(str.data(), "%d %d %d", &a, &b, &c);
      ++nflip;
      std::cout << "nflip= " << nflip << std::endl;
      add[nflip] = a;
      std::cout << "flipped address= " << add[nflip] << std::endl;
      val1[nflip][a] = b;
      val2[nflip][a] = c;
      std::cout << "value before flipped= " << val1[nflip][a] << std::endl;
      std::cout << "value after flipped= " << val2[nflip][a] << std::endl;
      std::cout << "-------------------------------count now=  " << count << std::endl;
      h2->Fill(count+1,add[nflip]);
    }
  }
  
  //set root file for output
  string foutname = "outputbitGR.root";
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

  //draw graph
  TCanvas *c1 = new TCanvas("c", "c",1000,1000);
  TGraph *grt = new TGraph(count);
  for(int j=1;j<count+1;++j){
    grt->SetPoint(j,j,tn[j]);
  }
  grt->SetMarkerStyle(20);
  grt->SetMarkerColor(kBlue);
  grt->SetMarkerSize(1.0);
  grt->SetTitle("fliped GR");
  grt->Draw("AP");

  /*
  //get values of each bits
  bool bits[16][n_Address][count];
  bool bits2[16][n_Address][count];

  for (unsigned row=0; row<n_Row; row+=1) {
    for (unsigned col=0; col<n_Col; col+=1) {
      for (int i=0; i<16; i+=1) {
	bool bv = ((val[col][row] >> i) & 0b1);
	bool bv2 = ((val2[col][row] >> i) & 0b1);
	bits[i][col][row] = bv; 
	bits2[i][col][row] = bv2; 
	//std::cout <<  bits2[i][col][row]; 
      }
      //std::cout << std::endl;
      //std::cout << "col= " << col << " row= " << row << " val= " << val2[col][row]  << std::endl;
    }
  }
  */

  /*
  //compare bits in 2 files
  int f[8] = {};
  int total= 0;
  for (unsigned row=0; row<n_Row; row+=1) {
    for (unsigned col=0; col<n_Col; col+=1) {
      for (int i=0; i<8; i+=1) {
	if(bits[i][col][row] != bits2[i][col][row]) {
	  ++f[i];
	  ++total;
	} 
      }
    }
  }
  for (int i=0; i<8; i+=1) {
    std::cout << "numbers of false bits in bit[" << i << "] = " << f[i] << std::endl;
    //summary << "bits[" << i << "]  " << f[i] << std::endl;
    //summary << f[i] << " " << std::endl;
  }
  */

  //Draw histograms
  TCanvas *c2 = new TCanvas("c2", "c2",1000,1000);
  h2->SetStats(0); 
  h2->Draw("col");

  //write in output file
  grt->Write();
  h2->Write();
  fout->Write();
  fout->Close();

  fin.close();

  std::cout << "#-----finished totalGR.cxx-----" << std::endl;
  return;

}


