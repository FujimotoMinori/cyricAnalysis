/*
    checkflipbitGR.C
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

int checkflipbitGR(const string& inputFile){
  std::cout << "#-----start analyzeGR.cxx-----" << std::endl;
 
  //set open file
  TString ifn = "/home/pixeldaq/cyric/afterIrrad/src/registerdata/run00029_GR00001.txt";
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

  //read file
  const int n_Address = 138;
  int a,b;
  int val[n_Address] = {};
  while(getline(fin,str))
  {
    if(str[0] == '#') continue;
    else if(str[0] == 'v') continue;
    a = 0; 
    b = 0; 
    sscanf(str.data(), "%d %d", &a, &b);
    val[a] = b;
  }

  int a2,b2;
  int val2[n_Address] = {};
  while(getline(fin2,str2))
  {
    if(str2[0] == '#') continue;
    else if(str2[0] == 'v') continue;
    a2 = 0; 
    b2 = 0; 
    sscanf(str2.data(), "%d %d", &a2, &b2);
    val2[a2] = b2;
  }

  //set root file for output
  string foutname = "Addressvsbit.root";
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

  //set file for summary output
  std::ofstream summary("checkbitGR.txt" ,std::ios::app);

  summary << "#inputFile=" <<ifn2 << std::endl;
  //get values of each bits
  bool bits[16][n_Address];
  bool bits2[16][n_Address];

  for (unsigned address=1; address<n_Address; address+=1) {
      std::cout << "address= " << address << std::endl;
      for (int i=0; i<16; i+=1) {
	bool bv = ((val[address] >> i) & 0b1);
	bool bv2 = ((val2[address] >> i) & 0b1);
	bits[i][address] = bv; 
	bits2[i][address] = bv2; 
      }
  }

  //compare value of GR
  int total= 0;
  std::cout << "# of address=  " << n_Address << std::endl;
  for(unsigned add=1; add<n_Address; ++add){
    if(val[add] != val2[add]){
      std::cout << "add= " << add << " is false  " << val[add] << "   " << val2[add] << std::endl;
      summary << add << " " << val[add] << " " << val2[add] << std::endl;
      total++;
    }
  }

  //make histograms
  TH2F* h2 = new TH2F("h2","flipped bit in each address",138,0,137,16,0,15);
  TH1F* h1 = new TH1F("h1","flipped bit in each address;address;# of flipped bit",138,0,137);
  //compare bits in 2 files
  int f[16] = {};
  int btotal= 0;
  for (unsigned address=1; address<n_Address; address+=1) {
    int fbit= 0;
    for (int i=0; i<16; i+=1) {
      if(bits[i][address] != bits2[i][address]) {
	++f[i];
	++btotal;
        ++fbit;
	h1->Fill(address);
      } 
      std::cout << "---------------------------------# of flipped bit in addr " << address << " = " << fbit << std::endl;
      h2->Fill(address,fbit);
    }
  }

  for (int i=0; i<16; i+=1) {
    std::cout << "numbers of false bits in bit[" << i << "] = " << f[i] << std::endl;
    //summary << "bits[" << i << "]  " << f[i] << std::endl;
    //summary << f[i] << " " << std::endl;
  }

  std::cout << "numbers of total false bits = " << btotal << std::endl;
  std::cout << "numbers of total false address = " << total << std::endl;
  summary << "totalbits " << btotal << std::endl;
  summary << "#totaladdress " << total << std::endl;

  //Draw histograms
  TCanvas *c1 = new TCanvas("c", "c",1000,1000);
  //h2->Draw("colz");
  h1->GetYaxis()->SetRangeUser(0,16);
  h1->SetStats(0);
  h1->Draw();

 
  fout->Write();
  fout->Close();
  summary.close();

  fin.close();
  fin2.close();

  std::cout << "#-----finished checkflipbitGR.cxx-----" << std::endl;
  return 0;

}


