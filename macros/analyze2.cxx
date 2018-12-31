/*
    analyze2.C
    compare two files
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

int analyze2(const string& inputFile){
  std::cout << "#-----start analyze2.cxx-----" << std::endl;
 
  //set open file
  TString ifn = "/home/pixeldaq/cyric/afterIrrad/src/registerdata/run00053_PR00001.txt";
  TString ifn2 = inputFile;
  std::cout << "#inputFile=" <<ifn2 << std::endl;
  ifstream fin;
  ifstream fin2;
  std::string str;
  std::string str2;

  //open files
  fin.open(ifn);
  if(fin.fail()){
    cerr << "#cannot open file1 : " << ifn << std::endl;
    return 1;
  }
  fin2.open(ifn2);
  if(fin2.fail()){
    cerr << "#cannot open file2 : " << ifn2 << std::endl;
    return 1;
  }
  std::cout << "#finished opening files" << std::endl;

  //read files
  const int n_Col = 400;
  const int n_Row = 192;
  int a,b,c;
  int val[n_Col][n_Row] = {};
  while(getline(fin,str))
  {
    if(str[0] == '#') continue;
    else if(str[0] == 'v') continue;
    a = 0; 
    b = 0; 
    c = 0; 
    sscanf(str.data(), "%d %d %d", &a, &b, &c);
    val[a][b] = c;
  }

  int a2,b2,c2;
  int val2[n_Col][n_Row] = {};
  while(getline(fin2,str2))
  {
    if(str2[0] == '#') continue;
    else if(str2[0] == 'v') continue;
    a2 = 0; 
    b2 = 0; 
    c2 = 0; 
    sscanf(str2.data(), "%d %d %d", &a2, &b2, &c2);
    val2[a2][b2] = c2;
  }

  //set root file for output
  string foutname = "output.root";
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

  //set file for summary output
  std::ofstream summary("summary.txt" ,std::ios::app);

  //make histograms
  TH2F *h0 = new TH2F("h0","bits[0];column;row",400,0,399,192,0,191);
  TH2F *h1 = new TH2F("h1","bits[1];column;row",400,0,399,192,0,191);
  TH2F *h2 = new TH2F("h2","bits[2];column;row",400,0,399,192,0,191);
  TH2F *h3 = new TH2F("h3","bits[3];column;row",400,0,399,192,0,191);
  TH2F *h4 = new TH2F("h4","bits[4];column;row",400,0,399,192,0,191);
  TH2F *h5 = new TH2F("h5","bits[5];column;row",400,0,399,192,0,191);
  TH2F *h6 = new TH2F("h6","bits[6];column;row",400,0,399,192,0,191);
  TH2F *h7 = new TH2F("h7","bits[7];column;row",400,0,399,192,0,191);

  //get values of each bits
  bool bits[8][n_Col][n_Row];
  bool bits2[8][n_Col][n_Row];
  // // [0] Pixel Enable / Pixel Power and Enable
  // // [1] Injection Enable
  // // [2] Hit-OR-bus Enable
  // // [3:6] TDAC value [6]=MSB
  // // [7]: TDAC sign / Gain Selection

  for (unsigned row=0; row<n_Row; row+=1) {
    for (unsigned col=0; col<n_Col; col+=1) {
      for (int i=0; i<8; i+=1) {
	bool bv = ((val[col][row] >> i) & 0b1);
	bool bv2 = ((val2[col][row] >> i) & 0b1);
	bits[i][col][row] = bv; 
	bits2[i][col][row] = bv2; 
      }
      if(bits2[0][col][row] == 0b1) h0->Fill(col,row); 
      if(bits2[1][col][row] == 0b1) h1->Fill(col,row); 
      if(bits2[2][col][row] == 0b1) h2->Fill(col,row); 
      if(bits2[3][col][row] == 0b1) h3->Fill(col,row); 
      if(bits2[4][col][row] == 0b1) h4->Fill(col,row); 
      if(bits2[5][col][row] == 0b1) h5->Fill(col,row); 
      if(bits2[6][col][row] == 0b1) h6->Fill(col,row); 
      if(bits2[7][col][row] == 0b1) h7->Fill(col,row); 
    }
  }

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
    summary << f[i] << " " << std::endl;
  }

  std::cout << "numbers of total false bits = " << total << std::endl;
  summary << "#inputFile=" <<ifn2 << std::endl;
  summary << "total " << total << std::endl;

  //Draw histograms
  TCanvas *c1 = new TCanvas("c", "c",1000,1000);
  gStyle->SetOptStat(11);
  c1->Divide(2,4);
  c1->cd(1); 
  h0->Draw("colz");
  c1->cd(2); 
  h1->Draw("colz");
  c1->cd(3); 
  h2->Draw("colz");
  c1->cd(4); 
  h3->Draw("colz");
  c1->cd(5); 
  h4->Draw("colz");
  c1->cd(6); 
  h5->Draw("colz");
  c1->cd(7); 
  h6->Draw("colz");
  c1->cd(8); 
  h7->Draw("colz");

 
  fout->Write();
  fout->Close();
  summary.close();

  fin.close();
  fin2.close();

  return 0;
  std::cout << "#-----finished analyze2.cxx-----" << std::endl;

}


