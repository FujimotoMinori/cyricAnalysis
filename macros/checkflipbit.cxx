/*
    checkflipbit.C
    compare two files
    count # of flipped bits/0->1/1->0
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

int checkflipbit(const string& inputFile){
  std::cout << "#-----start checkflipbit.cxx-----" << std::endl;
 
  //set open file
  TString ifn = "/home/pixeldaq/cyric/afterIrrad/src/registerdata/run00047_PR00001.txt";
  TString ifn2 = inputFile;
  
  TString name;
  name.Form("canv47.pdf");
  TCanvas* canv = new TCanvas(name.Data(),name.Data(),1000,800);
  canv->Print(name + "[","pdf");

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

  //read file
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
  //string foutname = "output.root";
  //TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

  //set file for summary output
  //std::ofstream summary("registerresults/summary.txt" ,std::ios::app);

  /*
  //make histograms
  TH2F *h0 = new TH2F("h0","bits[0];column;row",400,0,399,192,0,191);
  TH2F *h1 = new TH2F("h1","bits[1];column;row",400,0,399,192,0,191);
  TH2F *h2 = new TH2F("h2","bits[2];column;row",400,0,399,192,0,191);
  TH2F *h3 = new TH2F("h3","bits[3];column;row",400,0,399,192,0,191);
  TH2F *h4 = new TH2F("h4","bits[4];column;row",400,0,399,192,0,191);
  TH2F *h5 = new TH2F("h5","bits[5];column;row",400,0,399,192,0,191);
  TH2F *h6 = new TH2F("h6","bits[6];column;row",400,0,399,192,0,191);
  TH2F *h7 = new TH2F("h7","bits[7];column;row",400,0,399,192,0,191);
  */

  TH1F *htot = new TH1F("htot","bit flipped;# of bit;ratio of bit flip",8,0,8);
  TH1F *hbit0 = new TH1F("hbit0","bit flipped;# of bit;#of bit flip",8,0,8);
  TH1F *hbit1 = new TH1F("hbit1","bit flipped;# of bit;#of bit flip",8,0,8);

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
      /*
      if(bits2[0][col][row] == 0b1) h0->Fill(col,row); 
      if(bits2[1][col][row] == 0b1) h1->Fill(col,row); 
      if(bits2[2][col][row] == 0b1) h2->Fill(col,row); 
      if(bits2[3][col][row] == 0b1) h3->Fill(col,row); 
      if(bits2[4][col][row] == 0b1) h4->Fill(col,row); 
      if(bits2[5][col][row] == 0b1) h5->Fill(col,row); 
      if(bits2[6][col][row] == 0b1) h6->Fill(col,row); 
      if(bits2[7][col][row] == 0b1) h7->Fill(col,row); 
*/
    }
  }
  std::cout << "now here" << std::endl;

  //compare bits in 2 files
  double f[8] = {};
  double ef[8] = {};
  double f0[8] = {};
  double f1[8] = {};
  int total= 0;
  double total0= 0;
  double total1= 0;
  double nbit0= 0;
  double nbit1= 0;
  int nbitD= (136*2)*192;
  int nbitS= (128+136*2)*192;
  for (unsigned row=0; row<n_Row; row+=1) {
    for (unsigned col=0; col<n_Col; col+=1) {
      for (int i=0; i<8; i+=1) {

	//just to know the number of bit 0 or 1
	if(bits[i][col][row] == 1) nbit1++;
	else                       nbit0++; 

	//count flip bits
	if(bits[i][col][row] != bits2[i][col][row]) {
	  ++f[i];
	  ++total;
	  if(i%2 == 0){
	    if((col+row)%2 == 0){
	      ++f0[i];
	      total0++;
	    } else {
	      ++f1[i];
	      total1++;
	    }
	  } else {
	    if((col+row)%2 == 0) {
	      ++f1[i];
	      total1++;
	    } else {
	      ++f0[i];
	      total0++;
	    }
	  }
	}
      }
    }
  }

  
  for (int i=0; i<8; i++) {
    std::cout << "numbers of false bits in bit[" << i << "] = " << f[i] << std::endl;
    //summary << "bits[" << i << "]  " << f[i] << std::endl;
    //summary << f[i] << " " << std::endl;
    if(i == 0 | i == 1 | i == 2) {
            ef[i] = sqrt(f[i])/nbitS;
            //std::cout << "ef= " << ef[i] <<std::endl;
	    f[i] = f[i]/nbitS;
    }
    else {
            ef[i] = sqrt(f[i])/nbitD;
            //std::cout << "ef= " << ef[i] <<std::endl;
	    f[i] = f[i]/nbitD;
    }
    std::cout << "numbers of false bits in bit[" << i << "] = " << f[i] << std::endl;
    htot->Fill(i,f[i]);
    //std::cout << "error=" << htot->GetBinError(i) << std::endl;
    htot->SetBinError(i,ef[i]);
    std::cout << "value=" << htot->GetBinContent(i) << std::endl;
    std::cout << "error=" << htot->GetBinError(i) << std::endl;
    hbit0->Fill(i,f0[i]);
    hbit1->Fill(i,f1[i]);
  }

  double etotal0 = sqrt(total0);
  double etotal1 = sqrt(total1);
  double erate0,erate1;

  std::cout << "numbers of Sync false bits = " << nbitS << std::endl;
  std::cout << "numbers of Diff false bits = " << nbitD << std::endl;
  std::cout << "numbers of total false bits = " << total << std::endl;
  std::cout << "numbers of total0 false bits = " << total0 << std::endl;
  std::cout << "numbers of total1 false bits = " << total1 << std::endl;
  std::cout << "numbers of bit0 = " << nbit0 << std::endl;
  nbit0 = nbit1;
  std::cout << "numbers of bit0 = " << nbit0 << std::endl;
  std::cout << "numbers of bit1 = " << nbit1 << std::endl;
  std::cout << "ratio of total0 false bits = " << total0/nbit0 << "+-" << etotal0/nbit0 << std::endl;
  std::cout << "ratio of total1 false bits = " << total1/nbit1 << "+-" << etotal1/nbit1 << std::endl;
  //summary << "total " << total << std::endl;
  //summary << "total0 " << total0 << std::endl;
  //summary << "total1 " << total1 << std::endl;

  htot->GetYaxis()->SetRangeUser(0,0.0120);
  htot->SetStats(0);
  //std::cout << "number of bin=  " << htot->GetBinError(7) << std::endl;
  //std::cout << "error of bin0=  " << htot->GetBinError(0) << std::endl;
  htot->SetBinError(8,ef[7]);
  htot->Draw("hist e1");
  gPad->SetLeftMargin(0.15);
  canv->Print(name,"pdf");
  canv->Print(name + "]" ,"pdf");
  //htot->Draw("hist");
  /*
  canv->Print(name,"pdf");
  hbit0->Draw("hist");
  canv->Print(name,"pdf");
  hbit1->Draw("hist");
  canv->Print(name,"pdf");
  canv->Print(name + "]" ,"pdf");
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
  */
 
  //fout->Write();
  //fout->Close();
  //summary.close();

  fin.close();
  fin2.close();

  return 0;
  std::cout << "#-----finished checkflipbit.cxx-----" << std::endl;

}



