/*
    readCurrent2.C
    get the top of beam current
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
void readCurrent2(){
  std::cout << "#-----start readCurrent2.cxx-----" << std::endl;
 
	TH1F *h1 = new TH1F("h1","h1",100,-2.0e-9,2.0e-9);
	TH1F *h2 = new TH1F("h2","Dump current",38,0.,2.0e-9);
	
  //read data
	//ifstream ifs("dumpc.txt");
	ifstream ifs("DumpCurrent4.txt");
	std::cout << "set data" << std::endl;
	int i = 0;
	double val[1000000] = {};
	while(!ifs.eof()){
		 Double_t xx;
		  ifs >> xx ;
			i++;
			val[i] = xx;
			//if(i>12375&&i<14664){
			if(i>2521&&i<4810){
				h1->Fill(xx);
			}
	}
  std::cout << "i= " << i << std::endl;
  ifs.close();
  std::cout << "#finished reading files" << std::endl;

	//double max = 0.;
	double max[10000] = {};
	int k;
	//for(int j=12375;j<=14663;j++){
	for(int j=2521;j<=4819;j++){
		//std::cout << "val= " << val[j]<< std::endl;
		if(j%60 == 12375%60) {
			k++;
			max[k] = 0.;
		}
		if(val[j]>max[k]) max[k] = val[j];
	}

  //for(int l=1;l<=k;l++) h2->Fill(max[l]);
	
	double tmax;
	double mean;
	for(int m = 1;m<4;m++){
		tmax += max[m];
	}
	mean = tmax/3;
	std::cout << "mean= " << mean << std::endl;

	
	for(int l=1;l<=k;l++) {
	std::cout << "newval= " << (max[l]/mean)*1.0e-9 << std::endl;
		h2->Fill((max[l]/mean)*1.0e-9);
	}

  //fit histogram
	TF1 *f1 = new TF1("func","gaus",0.9e-9,1.8e-9);
	f1->SetParameter(0,6);
	f1->SetParameter(1,1.2e-9);
	f1->SetParameter(2,0.1e-9);
	h1->Fit("func","l","",0.9e-9,1.8e-9);

	h1->Draw();
	h2->Draw();

  return;
  std::cout << "#-----finished readCurrent2.cxx-----" << std::endl;

}


